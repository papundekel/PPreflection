#include "Enum.hpp"

#include "PP/functional/operators.hpp"
#include "PP/push_back_iterator.hpp"
#include "PP/transform_view.hpp"
#include "PP/unbounded.hpp"
#include "PP/view_copy.hpp"

#include "printers.hpp"

PPreflector::Enum::Enum(const clang::EnumDecl& decl, const descriptor& parent)
	: node_descriptor<clang::EnumType, nested_descriptor<descriptor, descriptor>>(*clang::dyn_cast_or_null<clang::EnumType>(decl.getTypeForDecl()), parent)
	, enum_values()
{
	PP::view_copy(PP::push_back_iterator(enum_values) ^ PP::unbounded, decl.enumerators() | PP::transform(PP::der));
}

void PPreflector::Enum::print_name_header(llvm::raw_ostream& out) const
{
	out << PPREFLECTOR_MEMBER_PRINT(print_qualified_name, *this);
}

void PPreflector::Enum::print_name_own(llvm::raw_ostream& out) const
{
	out << "::" << PPREFLECTOR_MEMBER_PRINT(print_name_header, *this);
}

void PPreflector::Enum::print_name_foreign(llvm::raw_ostream& out) const
{
	print_name_own(out);
}

void PPreflector::Enum::print_metadata_members(llvm::raw_ostream& out) const
{
	for (const auto& ev : enum_values)
		ev.print_metadata_name(out);
}

void PPreflector::Enum::print_metadata_traits(llvm::raw_ostream& out) const
{
	out << PPREFLECTOR_MEMBER_PRINT(print_metadata_name, *this) << "\n"
		<< PPREFLECTOR_MEMBER_PRINT(print_metadata_parent, *this) << "\n";

	print_members<"enum_values"_str>(out, enum_values, printer_value_tuple);
}

void PPreflector::Enum::print_metadata_object(llvm::raw_ostream&) const
{
	// print nothing
}
