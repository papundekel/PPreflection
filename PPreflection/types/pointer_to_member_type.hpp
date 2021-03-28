#pragma once
#include "pointer_to_member_type.h"

#include "../cv_qualification_signature.hpp"
#include "class_type.h"
#include "derived_from.hpp"

constexpr bool PPreflection::pointer_to_member_type::operator==(const pointer_to_member_type& other) const noexcept
{
	return
		get_class_type() == other.get_class_type() && 
		get_member_type() == other.get_member_type();
}

constexpr PPreflection::standard_conversion_sequence PPreflection::pointer_to_member_type::make_standard_conversion_sequence(const pointer_to_member_type& target) const noexcept
{
	standard_conversion_sequence sequence(*this);

	auto member_this = get_member_type();
	auto member_target = target.get_member_type();

	auto& class_this = get_class_type();
	auto& class_target = target.get_class_type();

	auto member_this_function_ptr = dynamic_cast<const function_type*>(&member_this.type);
	auto member_target_function_ptr = dynamic_cast<const function_type*>(&member_target.type);

	bool compatible_member_type = false;

	if (member_this_function_ptr && member_target_function_ptr)
	{
		auto convertible_rank = member_this_function_ptr->convertible_function_type(*member_this_function_ptr);
		if (convertible_rank == function_type::convertible_rank::Noexcept)
		{
			sequence.set_rank(conversion_sequence_rank::exact_match);
			sequence.set_function_noexcept(target.member_function_noexcept_conversion());
			compatible_member_type = true;
		}
	}
	else
	{
		if (member_this == member_target)
		{
			compatible_member_type = true;
		}
		else if (cv_qualification_signature(*this).compatible(cv_qualification_signature(target)))
		{
			sequence.set_rank(conversion_sequence_rank::exact_match);
			sequence.set_qualification();
			compatible_member_type = true;
		}
	}

	if (compatible_member_type)
	{
		if (class_this != class_target)
		{
			auto [is_derived, non_union_class_target, non_union_class_this] = derived_from(class_target, class_this);
			if (is_derived)
			{
				sequence.set_validity(target);
				sequence.set_rank(conversion_sequence_rank::conversion);
				sequence.set_promotion_conversion(base_pointer_conversion(*non_union_class_target));
			}
		}
		else
		{
			sequence.set_validity(target);
		}
	}

	return sequence;
}

constexpr PPreflection::standard_conversion_sequence PPreflection::pointer_to_member_type::make_standard_conversion_sequence(const non_array_object_type& target) const noexcept
{
	standard_conversion_sequence sequence(*this);

	if (const auto* target_pointer_to_member_ptr = dynamic_cast<const pointer_to_member_type*>(&target); target_pointer_to_member_ptr)
	{
		sequence = make_standard_conversion_sequence(*target_pointer_to_member_ptr);
	}
	else if (const auto* target_bool_ptr = dynamic_cast<const arithmetic_type_strong<bool>*>(&target); target_bool_ptr)
	{
		sequence.set_validity(target);
		sequence.set_rank(conversion_sequence_rank::conversion);
		sequence.set_promotion_conversion(bool_conversion());
	}

	return sequence;
}
