#pragma once
#include "non_array_object_type.h"

constexpr PPreflection::standard_conversion_sequence PPreflection::non_array_object_type::make_standard_conversion_sequence(const non_array_object_type& target, void*) const noexcept
{
	if (*this == target)
		return standard_conversion_sequence::create_identity(*this);
	else
		return make_standard_conversion_sequence(target);
}
