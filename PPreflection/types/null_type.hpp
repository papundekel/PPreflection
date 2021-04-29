#pragma once
#include "null_type.h"

#include "../conversion_sequence.h"
#include "pointer_base_type.h"

constexpr PPreflection::standard_conversion_sequence PPreflection::null_type::make_standard_conversion_sequence_impl(const non_array_object_type& target) const noexcept
{
	standard_conversion_sequence sequence;

	if (const auto* target_pointer_ptr = dynamic_cast<const pointer_base_type*>(&target); target_pointer_ptr)
	{
		sequence.set_validity(target);
		sequence.set_promotion_conversion(target_pointer_ptr->null_pointer_conversion());
	}

	return sequence;
}
