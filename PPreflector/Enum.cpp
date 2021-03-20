#include "Enum.hpp"

#include "PP/functional/operators.hpp"
#include "PP/push_back_iterator.hpp"
#include "PP/transform_view.hpp"
#include "PP/unbounded.hpp"
#include "PP/view_copy.hpp"

#include "print_wrap.hpp"
#include "strings.hpp"

PPreflector::Enum::Enum(const clang::EnumDecl& decl, const descriptor& parent)
	: node_descriptor<clang::EnumType, nested_descriptor<descriptor, descriptor>>(*clang::dyn_cast_or_null<clang::EnumType>(decl.getTypeForDecl()), parent)
	, enum_values()
{
	PP::view_copy(PP::push_back_iterator(enum_values) ^ PP::unbounded, decl.enumerators() | PP::transform(PP::der));
}

void PPreflector::Enum::print_name_header(llvm::raw_ostream& out) const
{
	out << PPREFLECTOR_PW(print_qualified_name, *this);
}

void PPreflector::Enum::print_name_own(llvm::raw_ostream& out) const
{
	out << "::" << PPREFLECTOR_PW(print_name_header, *this);
}

void PPreflector::Enum::print_name_foreign(llvm::raw_ostream& out) const
{
	print_name_own(out);
}

void PPreflector::Enum::print_metadata_implementation(llvm::raw_ostream& out) const
{
	print_metadata_name(out);
	print_metadata_parent(out);

	print_members(out, enum_values, "enum_values", "PP::value_tuple");

	for (const auto& ev : enum_values)
		ev.print_metadata_name(out);
}
