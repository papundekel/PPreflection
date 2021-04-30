#pragma once
#include "unknown_bound_array_type.h"

constexpr bool
PPreflection::unknown_bound_array_type::operator==(
	const unknown_bound_array_type& other) const noexcept
{
	return remove_extent() == other.remove_extent();
}
