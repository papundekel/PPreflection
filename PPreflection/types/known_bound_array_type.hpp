#pragma once
#include "known_bound_array_type.h"

constexpr bool PPreflection::known_bound_array_type::operator==(const known_bound_array_type& other) const noexcept
{
    return
        remove_extent() == other.remove_extent() &&
        get_extent() == other.get_extent();
}
