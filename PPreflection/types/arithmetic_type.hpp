#pragma once
#include "arithmetic_type.h"

#include "../conversion_sequence.h"

constexpr PPreflection::standard_conversion_sequence PPreflection::arithmetic_type::make_standard_conversion_sequence_impl(const non_array_object_type& target) const noexcept
{
	standard_conversion_sequence sequence(*this);

	if (const auto* target_arithmetic_ptr = dynamic_cast<const arithmetic_type*>(&target); target_arithmetic_ptr)
	{
		sequence.set_validity(target);
		sequence.set_rank(target == promoted_type() ? conversion_sequence_rank::promotion : conversion_sequence_rank::conversion);
		sequence.set_promotion_conversion(conversion(*target_arithmetic_ptr));
	}

	return sequence;
}
