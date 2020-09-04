#pragma once
#include "overloaded_conversion_function.h"
#include "conversion_function.h"

constexpr dynamic_object overloaded_conversion_function::invoke(dynamic_reference caller) const
{
	for (const conversion_function& f : get_overloads())
		if (f.can_invoke(caller))
			return f.invoke_unsafe(caller);

	return dynamic_object::create_invalid();
}
