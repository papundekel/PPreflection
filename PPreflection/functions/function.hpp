#pragma once
#include "../dynamic_object.h"
#include "../dynamic_reference.h"
#include "../types/parameter_type_reference.h"
#include "../types/type.h"
#include "args_to_arg_types.hpp"
#include "function.h"

constexpr void PPreflection::function::print_name_basic(PP::simple_ostream& out) const noexcept
{
	get_overloaded_function().print_name_after_parent(out);
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
constexpr bool PPreflection::function::has_name(PP::string_view name) const noexcept
{
	return get_overloaded_function().has_name(name);
}

constexpr bool PPreflection::function::can_invoke(PP::any_view<PP::iterator_category::ra, const reference_type&> argument_types) const noexcept
{
	return parameter_type_reference::can_initialize_many(parameter_types(), argument_types);
}

inline PPreflection::dynamic_variable PPreflection::function::invoke(PP::any_view<PP::iterator_category::ra, const dynamic_reference&> args) const
{
	if (can_invoke(args_to_arg_types(args)))
		return invoke_unsafe(PP::view_begin(args));
	else
		return dynamic_variable::create_invalid(dynamic_object::invalid_code::implicit_conversion_error);
}

inline PPreflection::dynamic_variable PPreflection::overloaded_function::invoke(PP::any_view<PP::iterator_category::ra, const dynamic_reference&> args) const
{
	for (const function& f : get_overloads())
		if (f.can_invoke(args_to_arg_types(args)))
			return f.invoke_unsafe(PP::view_begin(args));

	return dynamic_variable::create_invalid(dynamic_object::invalid_code::implicit_conversion_error);
}
