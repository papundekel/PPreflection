#pragma once
#include "../conversion_sequence.hpp"
#include "../dynamic_object.h"
#include "../dynamic_reference.h"
#include "../initialization.hpp"
#include "../types/parameter_type_reference.h"
#include "../types/type.h"
#include "function.h"

constexpr void PPreflection::function::print_name_basic(PP::simple_ostream& out) const noexcept
{
	print_name_implementation(out);
	type::print_parameter_types(out, parameter_types());
}

constexpr void PPreflection::function::print_noexcept(PP::simple_ostream& out) const noexcept
{
	if (is_noexcept())
		out.write(" noexcept");
}
constexpr void PPreflection::function::print_name_before_parent(PP::simple_ostream& out) const noexcept
{
	const descriptor& return_type_desc = return_type();
	return_type_desc.print_name(out);
	out.write(" ");
}
constexpr void PPreflection::function::print_name_after_parent(PP::simple_ostream& out) const noexcept
{
	print_name_basic(out);
	print_noexcept(out);
}

inline PPreflection::dynamic_variable PPreflection::function::invoke(PP::any_view<PP::iterator_category::ra, const dynamic_reference&>, void*) const noexcept
{
	return dynamic_variable::create_invalid(dynamic_object::invalid_code::implicit_conversion_error);
}
