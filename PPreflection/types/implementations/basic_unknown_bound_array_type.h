#pragma once
#include "../unknown_bound_array_type.h"

template <typename T>
class basic_unknown_bound_array_type : public unknown_bound_array_type
{
public:
	constexpr const complete_object_type& remove_extent() const noexcept
	{

	}
};
