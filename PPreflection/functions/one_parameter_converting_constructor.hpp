#pragma once
#include "one_parameter_converting_constructor.h"
#include "type.h"
#include "dynamic_reference.h"

constexpr PPreflection::dynamic_object PPreflection::one_parameter_converting_constructor::invoke(dynamic_reference arg) const
{
	if (arg.get_type().can_initialize(get_parameter_type()))
		return dynamic_object(return_type(),
			[this, arg](void* ptr)
			{
				invoke_implementation_one_parameter(ptr, arg);
			});
	else
		dynamic_object::create_invalid();
}
