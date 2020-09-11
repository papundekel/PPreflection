#pragma once
#include "complete_object_type.h"

class non_array_object_type : public complete_object_type
{
public:
	constexpr bool can_be_initialized(const reference_type& initializer) const noexcept
	{
		return true;
	}
};
