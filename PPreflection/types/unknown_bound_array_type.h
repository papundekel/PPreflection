#pragma once
#include "object_type.h"

class complete_object_type;

class unknown_bound_array_type : public object_type
{
public:
	constexpr virtual const complete_object_type& remove_extent() const noexcept = 0;
};
