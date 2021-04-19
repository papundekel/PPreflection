#pragma once
#include "pointer_type.h"

#include "../cv_qualification_signature.hpp"
#include "cv_type.h"
#include "derived_from.h"

constexpr PPreflection::standard_conversion_sequence PPreflection::pointer_type::make_standard_conversion_sequence_impl(const pointer_type& target) const noexcept
{
	standard_conversion_sequence sequence(*this);

	auto pointed_to_this = remove_pointer();
	auto pointed_to_target = target.remove_pointer();

	auto pointed_to_this_function_ptr = dynamic_cast<const function_type*>(&pointed_to_this.type);
	auto pointed_to_target_function_ptr = dynamic_cast<const function_type*>(&pointed_to_target.type);

	if (pointed_to_this_function_ptr && pointed_to_target_function_ptr)
	{
		auto convertible_rank = pointed_to_this_function_ptr->convertible_function_type(*pointed_to_target_function_ptr);
		if (convertible_rank == function_type::convertible_rank::Noexcept)
		{
			sequence.set_validity(target);
			sequence.set_rank(conversion_sequence_rank::exact_match);
			sequence.set_function_noexcept(pointed_to_this_function_ptr->function_noexcept_conversion());
		}
	}
	else if (pointed_to_target.cv >= pointed_to_this.cv)
	{
		auto [derived, pointed_to_this_class_ptr, pointed_to_target_class_ptr] = derived_from(pointed_to_this.type, pointed_to_target.type);

		if (derived)
		{
			sequence.set_validity(target);
			sequence.set_rank(conversion_sequence_rank::conversion);
			sequence.set_promotion_conversion(pointed_to_this_class_ptr->pointer_conversion_to_base(*pointed_to_target_class_ptr));
			sequence.set_converts_to_base_pointer();
			if (pointed_to_target.cv != pointed_to_this.cv)
				sequence.set_qualification();
		}
		else if (dynamic_cast<const void_type*>(&pointed_to_target.type))
		{
			sequence.set_validity(target);
			sequence.set_rank(conversion_sequence_rank::conversion);
			sequence.set_promotion_conversion(void_conversion());
			sequence.set_converts_to_void_pointer();
			if (pointed_to_target.cv != pointed_to_this.cv)
				sequence.set_qualification();
		}
		else if (cv_qualification_signature(*this) >= cv_qualification_signature(target))
		{
			sequence.set_validity(target);
			sequence.set_qualification();
		}
	}

	return sequence;
}

constexpr PPreflection::standard_conversion_sequence PPreflection::pointer_type::make_standard_conversion_sequence_impl(const non_array_object_type& target) const noexcept
{
	standard_conversion_sequence sequence(*this);

	if (const auto* target_pointer_ptr = dynamic_cast<const pointer_type*>(&target); target_pointer_ptr)
	{
		sequence = make_standard_conversion_sequence_impl(*target_pointer_ptr);
	}
	else if (const auto* target_bool_ptr = dynamic_cast<const arithmetic_type_strong<bool>*>(&target); target_bool_ptr)
	{
		sequence.set_validity(target);
		sequence.set_rank(conversion_sequence_rank::conversion);
		sequence.set_promotion_conversion(bool_conversion());
		sequence.set_converts_pointer_to_bool();
	}

	return sequence;
}
