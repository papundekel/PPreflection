#pragma once
#include "dynamic_array_type.h"

namespace PPreflection::detail
{
class dynamic_unknown_bound_array_type final
	: public dynamic_array_type<unknown_bound_array_type>
{
public:
	using dynamic_array_type<unknown_bound_array_type>::dynamic_array_type;
};
}
