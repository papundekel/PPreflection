#pragma once
#include "../dynamic_reference.h"
#include "../types/type.h"
#include "one_parameter_converting_constructor.h"

inline PPreflection::dynamic_object PPreflection::one_parameter_converting_constructor::invoke(dynamic_reference arg) const
{
	//if (get_parameter_type().can_be_initialized(arg.get_type()))
		return invoke_unsafe(arg);
	//else
	//	return dynamic_object::create_invalid(dynamic_object::invalid_code::implicit_conversion_error);
}
