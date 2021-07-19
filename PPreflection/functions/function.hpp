#pragma once
#include "../dynamic_object.h"
#include "../dynamic_reference.h"
#include "../types/parameter_type_reference.h"
#include "../types/type.h"
#include "function.h"

constexpr void PPreflection::function::print_name_basic(
	PP::ostream& out) const noexcept
{
	print_name_implementation(out);
	type::print_parameter_types(out, parameter_types());
}

constexpr void PPreflection::function::print_noexcept(
	PP::ostream& out) const noexcept
{
	if (is_noexcept())
		out.write(" noexcept");
}

constexpr void PPreflection::function::print_name_before_parent(
	PP::ostream& out) const noexcept
{
	return_type().as_type().print_name_prefix(out);
	out.write(" ");
}

constexpr void PPreflection::function::print_name_after_parent(
	PP::ostream& out) const noexcept
{
	print_name_basic(out);
	print_noexcept(out);
	return_type().as_type().print_name_suffix(out);
}
