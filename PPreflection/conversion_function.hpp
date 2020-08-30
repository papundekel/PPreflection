#pragma once
#include "conversion_function.h"

constexpr void conversion_function::invoke_implementation_member(void* result, const dynamic_reference& caller, const dynamic_reference*) const noexcept
{
	invoke_implementation_conversion(result, caller);
}
constexpr dynamic_object conversion_function::invoke_unsafe(const dynamic_reference& caller) const noexcept
{
	return dynamic_object(return_type(),
		[this, &caller](void* ptr)
		{
			invoke_implementation_conversion(ptr, caller);
		});
}

constexpr dynamic_object conversion_function::invoke(const dynamic_reference& caller) const
{
	if (can_invoke(caller))
		return invoke_unsafe(caller);
	else
		throw 0;
}
