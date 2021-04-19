#include "Class.hpp"

#include "PP/push_back_iterator.hpp"
#include "PP/view_chain.hpp"

PPreflector::Class::Class(const clang::CXXRecordDecl& decl, const descriptor& parent)
	: node_descriptor<clang::RecordType, nested_descriptor<descriptor, descriptor>>(*clang::dyn_cast_or_null<clang::RecordType>(decl.getTypeForDecl()), parent)
	, nested_types()
	, base_classes()
	, constructors()
	, static_member_functions()
	, non_conversion_member_functions()
	, conversion_functions()
{
	PP::view_copy(PP::push_back_iterator(base_classes) ^ PP::unbounded, decl.bases() | PP::transform([]
		(const clang::CXXBaseSpecifier& base) -> auto&
		{
			return *base.getType().getTypePtr();
		}));

	for (const auto* method_ptr : decl.methods())
	{
		const auto& method = *method_ptr;

		if (method.isTemplated() || 
			clang::isa<clang::CXXConstructorDecl>(method) ||
			clang::isa<clang::CXXDestructorDecl>(method))
			continue;

		if (method.isStatic())
			static_member_functions.emplace_back(method, *this);
		else if (const auto* conversion_method_ptr = clang::dyn_cast<clang::CXXConversionDecl>(&method); conversion_method_ptr)
			conversion_functions.emplace_back(*conversion_method_ptr, *this);
		else
			non_conversion_member_functions.emplace_back(method, *this);
	}

	for (const auto* constructor_ptr : decl.ctors())
	{
		const auto& constructor = *constructor_ptr;

		if (constructor.isTemplated())
			continue;

		constructors.emplace_back(constructor, *this);
	}
}

void PPreflector::Class::print_name_header(llvm::raw_ostream& out) const
{
	out << PPREFLECTOR_MEMBER_PRINT(print_qualified_name, *this);
}

void PPreflector::Class::print_name_own(llvm::raw_ostream& out) const
{
	out << "::" << PPREFLECTOR_MEMBER_PRINT(print_name_header, *this);
}

void PPreflector::Class::print_name_foreign(llvm::raw_ostream& out) const
{
	print_name_own(out);
}

void PPreflector::Class::print_metadata_members(llvm::raw_ostream& out) const
{
	for (const descriptor& d : PP::view_chain(
			as_descriptors_view(nested_types)) ^
			as_descriptors_view(constructors) ^
			as_descriptors_view(static_member_functions) ^
			as_descriptors_view(non_conversion_member_functions) ^
			as_descriptors_view(conversion_functions))
		d.print_metadata(out);
}

void PPreflector::Class::print_metadata_traits(llvm::raw_ostream& out) const
{
	out << PPREFLECTOR_MEMBER_PRINT(print_metadata_name, *this) << "\n"
		<< PPREFLECTOR_MEMBER_PRINT(print_metadata_parent, *this) << "\n";

	print_members<"nested_types"_str>(out, nested_types, printer_type_tuple) << "\n";
	print_members<"base_classes"_str>(out, base_classes, printer_type_tuple) << "\n";
	print_members<"constructors"_str>(out, constructors, printer_make_tuple) << "\n";
	print_members<"static_member_functions"_str>(out, static_member_functions, printer_value_tuple) << "\n";
	print_members<"non_conversion_member_functions"_str>(out, non_conversion_member_functions, printer_value_tuple) << "\n";
	print_members<"conversion_functions"_str>(out, conversion_functions, printer_value_tuple) << "\n";
}

void PPreflector::Class::print_metadata_object(llvm::raw_ostream&) const
{
	// print nothing
}
