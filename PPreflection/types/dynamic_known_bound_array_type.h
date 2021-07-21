#pragma once
#include "dynamic_array_type.h"

namespace PPreflection::detail
{
class dynamic_known_bound_array_type final
	: public dynamic_array_type<known_bound_array_type>
{
	size_t extent;

public:
	constexpr explicit dynamic_known_bound_array_type(
		cv_type<complete_object_type> inner_type,
		PP::size_t extent) noexcept
		: dynamic_array_type<known_bound_array_type>(inner_type)
		, extent(extent)
	{}

	constexpr PP::size_t get_extent() const noexcept override final
	{
		return extent;
	}
};
}
