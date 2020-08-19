#pragma once
#include "member_function.h"
#include "dynamic_ptr.h"
#include "function.h"

constexpr bool member_function::can_invoke(const dynamic_ptr& caller_arg) const noexcept
{
	const type& caller_par_type = get_caller_parameter_type();
	const type& caller_arg_type = caller_arg.get_type();

	if (get_ref_qualifier() == ref_qualifier::none)
		return caller_arg_type.can_reference_initialize(caller_par_type.add_lreference()) || caller_arg_type.can_reference_initialize(caller_par_type.add_rreference());
	else
		return caller_arg_type.can_reference_initialize(caller_par_type);
}

constexpr void member_function::invoke_implementation(void* result, const dynamic_ptr* args) const noexcept
{
	invoke_implementation_member(result, args[0], args + 1);
}

constexpr bool member_function::can_invoke(simple_range<const dynamic_ptr> args) const noexcept
{
	return !args.empty() && can_invoke(args[0]) && function::can_invoke(simple_range(args.begin() + 1, args.end()));
}

constexpr dynamic_wrap member_function::invoke_unsafe(const dynamic_ptr& caller, simple_range<const dynamic_ptr> args) const
{
	return dynamic_wrap(return_type(), [this, &caller, args](void* ptr) { invoke_implementation_member(ptr, caller, args.begin()); });
}

constexpr dynamic_wrap member_function::invoke(const dynamic_ptr& caller, simple_range<const dynamic_ptr> args) const
{
	if (can_invoke(caller) && function::can_invoke(args))
		return invoke_unsafe(caller, args);
	else
		throw 0; //TODO
}
