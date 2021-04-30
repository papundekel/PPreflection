#pragma once
#include "dynamic_object.h"
#include "dynamic_reference.h"

namespace PPreflection
{
	inline dynamic_object qualification_conversion(
		dynamic_reference			 r,
		const non_array_object_type& target)
	{
		return dynamic_object::create_shallow_copy(r).cast(target);
	}
}
