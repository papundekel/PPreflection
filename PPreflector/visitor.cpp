#include "visitor.hpp"

#include "print_wrap.hpp"

PPreflector::visitor::visitor(clang::CompilerInstance& ci)
	: context(ci.getASTContext())
	, global()
	, map_namespaces()
{}

bool PPreflector::visitor::VisitDecl(clang::Decl* declaration)
{
	if (auto* named_declaration_p = clang::dyn_cast<clang::NamedDecl>(declaration); named_declaration_p && !clang::isa<clang::ParmVarDecl>(named_declaration_p))
	{
		auto& named_declaration = *named_declaration_p;
		if (is_reserved(named_declaration))
			return true;

		if (auto* namespace_declaration_p = clang::dyn_cast<clang::NamespaceDecl>(named_declaration_p))
		{
			auto& namespace_declaration = *namespace_declaration_p;

			if (!namespace_declaration.isFirstDecl() ||
				namespace_declaration.isStdNamespace())
				return true;

			register_namespace(namespace_declaration);
		}
		else if (auto* function_declaration_p = clang::dyn_cast<clang::FunctionDecl>(named_declaration_p))
		{
			auto& function_declaration = *function_declaration_p;

			if (!function_declaration.isFirstDecl() ||
				function_declaration.isTemplated() ||
				function_declaration.isMain() ||
				function_declaration.isVariadic())
				return true;

			// is namespace function
			if (auto* parent_namespace_p = get_namespace_parent(function_declaration))
			{
				parent_namespace_p->add(function_declaration);
			}
		}
		else if (auto* enum_declaration_p = clang::dyn_cast<clang::EnumDecl>(named_declaration_p))
		{
			auto& enum_declaration = *enum_declaration_p;

			if (!enum_declaration.isFirstDecl() ||
				!enum_declaration.getIdentifier())
				return true;

			// is enum in namespace scope
			if (auto* parent_namespace_p = get_namespace_parent(enum_declaration))
			{
				parent_namespace_p->add(enum_declaration);
			}
		}
	}
	
	return true;
}

void PPreflector::visitor::print(llvm::raw_ostream& out) const
{
	out <<	"#ifndef PPREFLECTOR_GUARD\n"
			"#pragma once\n"
			"#include \"PP/value_tuple.hpp\"\n"
			"\n"
			"#include \"PPreflection/reflect.hpp\"\n"
			"\n"
			"namespace PPreflection::tags\n"
			"{\n"
		<<	PPREFLECTOR_PW(print_layout, global)
		<< 	"}\n";
	
	global.print_metadata(out);

	out << 	"\n"
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

	auto& child_namespace = parent->add(child_declaration);

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
			return ii->getName().contains("__");
	}

	return false;
}
