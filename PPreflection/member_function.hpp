#pragma once
#include "member_function.h"
#include "dynamic_reference.h"
#include "function.h"

constexpr void member_function::print_name(simple_ostream& out) const noexcept
{
	print_name_basic(out);

	switch (get_cv_qualifier())
	{
	case cv_qualifier::const_:
		out.write(" const"); break;
	case cv_qualifier::volatile_: break;
		out.write(" volatile"); break;
	case cv_qualifier::const_volatile:
		out.write(" const volatile"); break;
	}

	switch (get_ref_qualifier())
	{
	case ref_qualifier::lvalue:
		out.write("&"); break;
	case ref_qualifier::rvalue:
		out.write("&&"); break;
	}

	print_noexcept(out);
}
constexpr bool member_function::has_name(std::string_view name) const noexcept
{
	// TODO
	return false;
}

constexpr bool member_function::can_invoke(const type& caller_arg_type) const noexcept
{
	const type& caller_par_type = get_caller_parameter_type();

	if (get_ref_qualifier() == ref_qualifier::none)
		return caller_arg_type.can_reference_initialize(caller_par_type.add_lreference()) || caller_arg_type.can_reference_initialize(caller_par_type.add_rreference());
	else
		return caller_arg_type.can_reference_initialize(caller_par_type);
}

constexpr dynamic_object member_function::invoke_unsafe(any_iterator<const dynamic_reference&> arg_iterator) const noexcept
{
	return invoke_unsafe_member(arg_iterator[0], arg_iterator + 1);
}

constexpr bool member_function::can_invoke(any_view<const type&> argument_types) const noexcept
{
	return !PP::empty(argument_types) && can_invoke(argument_types[0]) && function::can_invoke(1 >> argument_types);
}

constexpr dynamic_object member_function::invoke(dynamic_reference caller, pointer_view<const dynamic_reference> args) const
{
	if (can_invoke(caller.get_type()) && function::can_invoke(args | PP::transform([](const dynamic_reference& r) -> const type& { return r.get_type(); })))
		return invoke_unsafe_member(caller, PP::begin(args));
	else
		return dynamic_object::create_invalid();
}
