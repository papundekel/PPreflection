#pragma once
#include "dynamic_array_type.h"

class dynamic_known_bound_array_type final : public dynamic_array_type<known_bound_array_type>
{
	std::size_t extent;

public:
	constexpr explicit dynamic_known_bound_array_type(const complete_object_type& inner_type, std::size_t extent) noexcept
		: dynamic_array_type<known_bound_array_type>(inner_type)
		, extent(extent)
	{}

	constexpr std::size_t get_extent() const noexcept override final
	{
		return extent;
	}
};
