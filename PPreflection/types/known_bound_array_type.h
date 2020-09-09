#pragma once
#include "complete_object_type.h"

class known_bound_array_type : public complete_object_type
{
public:
	constexpr virtual const complete_object_type& remove_extent() const noexcept = 0;
};
