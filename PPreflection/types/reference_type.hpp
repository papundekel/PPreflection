#pragma once
#include "reference_type.h"

constexpr void PPreflection::reference_type::print_name_prefix(
	PP::ostream& out) const noexcept
{
	remove_reference().print_name_prefix(out);

	out.write("(&");
	if (!is_lvalue())
		out.write("&");
}
constexpr void PPreflection::reference_type::print_name_suffix(
	PP::ostream& out) const noexcept
{
	out.write(")");
	remove_reference().print_name_suffix(out);
}

constexpr bool PPreflection::reference_type::operator==(
	const reference_type& other) const noexcept
{
	return remove_reference() == other.remove_reference();
}
