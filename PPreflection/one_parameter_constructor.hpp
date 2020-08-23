#pragma once
#include "one_parameter_constructor.h"

constexpr dynamic_object one_parameter_constructor::invoke(const dynamic_reference& arg) const
{
	return dynamic_object(return_type(),
		[this, &arg](void* ptr)
		{
			invoke_implementation(ptr, &arg);
		});
}
