#pragma once
#include "conversion_function.h"

inline PPreflection::dynamic_variable PPreflection::overloaded_conversion_function::invoke(dynamic_reference caller) const
{
	for (const conversion_function& f : get_overloads())
		if (f.can_invoke(caller.get_type()))
			return f.invoke_unsafe_conversion(caller);

	return dynamic_variable::create_invalid(dynamic_object::invalid_code::implicit_conversion_error);
}
