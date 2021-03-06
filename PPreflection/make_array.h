#pragma once
#include "types/dynamic_unknown_bound_array_type.h"
#include "types/dynamic_known_bound_array_type.h"

namespace PPreflection
{
	constexpr auto make_array(const complete_object_type& inner_type, PP::size_t extent) noexcept
	{
		return dynamic_known_bound_array_type(inner_type, extent);
	}
	constexpr auto make_array(const complete_object_type& inner_type) noexcept
	{
		return dynamic_unknown_bound_array_type(inner_type);
	}
}
