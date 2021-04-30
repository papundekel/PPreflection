#pragma once
#include "array_type.h"

#include "../conversion_sequence.h"
#include "pointer_type.h"

template <typename Base>
constexpr PPreflection::standard_conversion_sequence
PPreflection::detail::array_type<Base>::make_standard_conversion_sequence(
	const non_array_object_type& target) const noexcept
{
	auto sequence =
		get_pointer_to_element().make_standard_conversion_sequence(target);
	sequence.set_to_pointer(array_to_pointer_conversion());
	return sequence;
}
