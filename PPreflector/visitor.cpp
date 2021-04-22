#include "visitor.hpp"

#include "pragma_push.hpp"
#include "llvm/Support/raw_ostream.h"
#include "pragma_pop.hpp"

#include "for_each_with_delimiters.hpp"
#include "printers.hpp"

PPreflector::visitor::visitor(clang::CompilerInstance& ci)
	: context(ci.getASTContext())
	, global()
	, map_namespaces()
{}

bool PPreflector::visitor::VisitDecl(clang::Decl* declaration)
{
	if (auto* named_declaration_ptr = clang::dyn_cast<clang::NamedDecl>(declaration); named_declaration_ptr && !clang::isa<clang::ParmVarDecl>(named_declaration_ptr))
	{
		auto& named_declaration = *named_declaration_ptr;
		if (is_reserved(named_declaration) ||
			named_declaration.isTemplated())
			return true;

		if (auto* namespace_declaration_ptr = clang::dyn_cast<clang::NamespaceDecl>(named_declaration_ptr))
		{
			auto& namespace_declaration = *namespace_declaration_ptr;

			if (!namespace_declaration.isFirstDecl() ||
				namespace_declaration.isStdNamespace() ||
				namespace_declaration.isAnonymousNamespace())
				return true;

			register_namespace(namespace_declaration);
		}
		else if (auto* function_declaration_ptr = clang::dyn_cast<clang::FunctionDecl>(named_declaration_ptr))
		{
			auto& function_declaration = *function_declaration_ptr;

			if (!function_declaration.isFirstDecl() ||
				function_declaration.isMain() ||
				function_declaration.isVariadic() || 
				function_declaration.isOverloadedOperator())
				return true;

			// is namespace function
			if (auto* parent_namespace_p = get_namespace_parent(function_declaration))
			{
				parent_namespace_p->add(function_declaration);
			}
		}
		else if (auto* enum_declaration_ptr = clang::dyn_cast<clang::EnumDecl>(named_declaration_ptr))
		{
			auto& enum_declaration = *enum_declaration_ptr;

			if (!enum_declaration.isFirstDecl() ||
				!enum_declaration.getIdentifier())
				return true;

			// is enum in namespace scope
			if (auto* parent_namespace_ptr = get_namespace_parent(enum_declaration))
			{
				parent_namespace_ptr->add(enum_declaration);
			}
		}
		else if (auto* class_declaration_ptr = clang::dyn_cast<clang::CXXRecordDecl>(named_declaration_ptr))
		{
			auto& class_declaration = *class_declaration_ptr;

			if (!class_declaration.isFirstDecl() ||
				!class_declaration.hasDefinition() ||
				clang::isa<clang::ClassTemplateSpecializationDecl>(class_declaration) ||
				class_declaration.isUnion())
				return true;

			if (auto* p = class_declaration.getTypedefNameForAnonDecl(); p && is_reserved(*p))
				return true;

			// is class in namespace scope
			if (auto* parent_namespace_ptr = get_namespace_parent(class_declaration))
			{
				classes.push_back(parent_namespace_ptr->add(class_declaration));
			}
		}
	}
	
	return true;
}

void PPreflector::visitor::print(llvm::raw_ostream& out) const
{
	out <<	"#ifndef PPREFLECTOR_GUARD\n"
			"#pragma once\n"
			"#include \"PPreflection/meta.hpp\"\n"
			"\n"
			"namespace PPreflection::tags\n"
			"{\n"
		<<	PPREFLECTOR_MEMBER_PRINT(print_layout, global)
		<< 	"}\n"
		<<	PPREFLECTOR_MEMBER_PRINT(print_metadata, global) << "\n"
			"namespace PPreflection\n"
			"{\n"
			"\tconstexpr inline const Namespace& global_namespace = reflect(PP::type<tags::global>);\n"
			"}\n"
			"\n"
			"const PPreflection::non_union_class_type& PPreflection::reflect_polymorphic(std::type_index type)\n"
			"{\n"
			"\tstatic const auto map = type_info_map(PP::type_tuple<\n";

	for_each_with_delimiters([&out]
		(const Class& c)
		{
			out << "\t\t" << PPREFLECTOR_MEMBER_PRINT(print_name_foreign, c);
		}, [&out]
		()
		{
			out << ",\n";
		}, classes);

	out <<	">);\n"
			"\n"
			"\treturn map.get(type);\n"
			"}\n"
			"\n"
			"#endif\n";
}

void PPreflector::visitor::clear_temps()
{
	map_namespaces.clear();
}

void PPreflector::visitor::remove_unwanted()
{
	global.remove_std();
}

PPreflector::Namespace* PPreflector::visitor::get_namespace_parent(clang::DeclContext& declaration_context)
{
	auto* parent = declaration_context.getParent();
	if (parent)
	{
		if (auto* namespace_parent = clang::dyn_cast_or_null<clang::NamespaceDecl>(parent))
		{
			auto i = map_namespaces.find(namespace_parent->getOriginalNamespace());
			if (i != map_namespaces.end())
				return &i->second.get();
			else
				return nullptr;
		}
		else if (clang::isa<clang::TranslationUnitDecl>(parent))
			return &global;
		else
			return nullptr;
	}
	else
	{
		llvm::outs() << "saujimave\n";
		return &global;
	}
}

void PPreflector::visitor::register_namespace(clang::NamespaceDecl& child_declaration)
{	
	auto* parent = get_namespace_parent(child_declaration);

	if (!parent)
		return;

	[[maybe_unused]] auto& child_namespace = parent->add(child_declaration);

	assert(map_namespaces.try_emplace(&child_declaration, child_namespace).second);
}

llvm::raw_ostream& PPreflector::visitor::print_name(llvm::raw_ostream& out, const clang::NamedDecl& d)
{
	out << "::";
	d.printQualifiedName(out);
	return out;
}

bool PPreflector::visitor::is_reserved(const clang::NamedDecl& d)
{
	auto declname = d.getDeclName();
	if (declname.isIdentifier())
	{
		auto* ii = declname.getAsIdentifierInfo();
		if (ii)
		{
			auto name = ii->getName();
			return name.contains("__") || (name.size() >= 2 && name[0] == '_' && name[1] >= 'A' && name[1] <= 'Z');
		}
	}

	return false;
}

//bool PPreflector::visitor::shouldTraversePostOrder() const
//{
//	return true;
//}
