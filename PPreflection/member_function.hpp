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

constexpr bool member_function::can_invoke(dynamic_reference caller_arg) const noexcept
{
	const type& caller_par_type = get_caller_parameter_type();
	const type& caller_arg_type = caller_arg.get_type();

	if (get_ref_qualifier() == ref_qualifier::none)
		return caller_arg_type.can_reference_initialize(caller_par_type.add_lreference()) || caller_arg_type.can_reference_initialize(caller_par_type.add_rreference());
	else
		return caller_arg_type.can_reference_initialize(caller_par_type);
}

constexpr void member_function::invoke_implementation(void* result, const dynamic_reference* args) const noexcept
{
	invoke_implementation_member(result, args[0], args + 1);
}

constexpr bool member_function::can_invoke(pointer_view<const dynamic_reference> args) const noexcept
{
	return !PP::empty(args) && can_invoke(args[0]) && function::can_invoke(1 >> args);
}

constexpr dynamic_object member_function::invoke_unsafe(dynamic_reference caller, pointer_view<const dynamic_reference> args) const
{
	return dynamic_object(return_type(), [this, caller, args](void* ptr) { invoke_implementation_member(ptr, caller, args.begin()); });
}

constexpr dynamic_object member_function::invoke(dynamic_reference caller, pointer_view<const dynamic_reference> args) const
{
	if (can_invoke(caller) && function::can_invoke(args))
		return invoke_unsafe(caller, args);
	else
		dynamic_object::create_invalid();
}
