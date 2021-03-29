#pragma once
#include "PP/array.hpp"

#include "conversion_sequence.hpp"
#include "overload_resolution.h"
#include "types/class_type.h"
#include "types/derived_from.hpp"

namespace PPreflection
{
	constexpr bool valid_return_type_for_conversion(return_type_reference return_type, const class_type& target_type) noexcept
	{
		return return_type.visit(PP::overloaded
		(
			[&target_type](const non_array_object_type& t){ return same_or_derived_from(t, target_type); },
			[&target_type](const reference_type& rt){ return same_or_derived_from(rt.remove_reference().type, target_type); },
			[](const void_type&){ return false; }
		));
	}

	constexpr standard_conversion_sequence valid_return_type_for_conversion(return_type_reference return_type, const non_array_object_type& target_type) noexcept
	{
		return return_type.visit(PP::overloaded
		(
			[&target_type](const non_array_object_type& t) { return t.make_standard_conversion_sequence(target_type); },
			[&target_type](const reference_type& rt) { return rt.remove_reference().type.make_standard_conversion_sequence(target_type); },
			[](const void_type&){ return standard_conversion_sequence::create_invalid(); }
		));
	}

	constexpr implicit_conversion_sequence initialization_sequence(const non_array_object_type& target_type, const referencable_type& initializer_type_non_class)
	{
		auto standard_sequence = initializer_type_non_class.make_standard_conversion_sequence(target_type);

		if (standard_sequence.is_identity())
			standard_sequence.set_load(target_type);

		return implicit_conversion_sequence::create_standard(standard_sequence);
	}
	
	constexpr void push_constructor_candidates(
		const class_type& target_type,
		auto& candidates,
		auto& return_value_sequences)
	{
		for (const auto& c : target_type.get_constructors())
		{
			if (!c.is_explicit())
			{
				candidates.push_back(c);
				return_value_sequences.push_back(standard_conversion_sequence::create_identity());
			}
		}
	}

	constexpr void push_conversion_candidates(
		const class_type& target_type,
		const class_type& initializer_type,
		auto& candidates,
		auto& return_value_sequences,
		bool can_use_user_defined)
	{
		bool same_or_derived = same_or_derived_from(initializer_type, target_type);

		if (same_or_derived || can_use_user_defined)
		{
			push_constructor_candidates(target_type, candidates, return_value_sequences);
		}
		else if (!same_or_derived && can_use_user_defined)
		{
			PP::simple_vector<PP::reference_wrapper<const conversion_function&>> conversion_functions;
			initializer_type.get_conversion_functions_inherited(PP::push_back_iterator(conversion_functions));

			for (const conversion_function& cf : conversion_functions)
			{
				if (!cf.is_explicit() && valid_return_type_for_conversion(cf.return_type(), target_type))
				{
					candidates.push_back(cf);
					if (cf.return_type().as_type() != target_type)
						return_value_sequences.push_back(standard_conversion_sequence::create_load(target_type));
					else
						return_value_sequences.push_back(standard_conversion_sequence::create_identity());
				}
			}
		}
	}

	constexpr void push_conversion_candidates(
		const non_array_object_type& target_type,
		const class_type& initializer_type,
		auto& candidates,
		auto& return_value_sequences)
	{
		PP::simple_vector<PP::reference_wrapper<const conversion_function&>> conversion_functions;
		initializer_type.get_conversion_functions_inherited(PP::push_back_iterator(conversion_functions));

		for (const conversion_function& cf : conversion_functions)
		{
			auto sequence = valid_return_type_for_conversion(cf.return_type(), target_type);

			if (!cf.is_explicit() && sequence.is_valid())
			{
				candidates.push_back(cf);
				return_value_sequences.push_back(sequence);
			}
		}
	}

	constexpr implicit_conversion_sequence initialization_sequence(const non_array_object_type& target_type, const reference_type& initializer_type, bool can_use_user_defined)
	{
		const auto* target_type_class_ptr = dynamic_cast<const class_type*>(&target_type);
		const auto* initializer_type_class_ptr = dynamic_cast<const class_type*>(&initializer_type.remove_reference().type);

		if (!target_type_class_ptr && !initializer_type_class_ptr)
			return initialization_sequence(target_type, initializer_type.remove_reference().type);
		else
		{
			PP::simple_vector<PP::reference_wrapper<const function&>> candidates(4);
			PP::simple_vector<standard_conversion_sequence> return_value_sequences(4);

			if (target_type_class_ptr)
			{
				const auto& target_type_class = *target_type_class_ptr;
				if (initializer_type_class_ptr)
					push_conversion_candidates(target_type_class, *initializer_type_class_ptr, candidates, return_value_sequences, can_use_user_defined);
				else if (can_use_user_defined)
					push_constructor_candidates(target_type_class, candidates, return_value_sequences);
			}
			else if (initializer_type_class_ptr && can_use_user_defined)
				push_conversion_candidates(target_type, *initializer_type_class_ptr, candidates, return_value_sequences);

			auto [result, error_code] = overload_resolution(candidates, PP::forward_as_array(initializer_type), return_value_sequences, false);

			if (result)
				return result->make_conversion_sequence();
			else if (error_code == overload_resolution_error::ambiguous)
				return implicit_conversion_sequence::create_ambiguous();
			else// if (error_code == overload_resolution_error::invalid)
				return implicit_conversion_sequence::create_invalid();
		}
	}

	constexpr implicit_conversion_sequence initialization_sequence(const reference_type&, const reference_type&, bool)
	{
		return implicit_conversion_sequence::create_invalid();
	}

	constexpr implicit_conversion_sequence initialization_sequence(parameter_type_reference target_type, const reference_type& initializer_type, bool can_use_user_defined)
	{
		return target_type.visit([&initializer_type, can_use_user_defined]
			(const auto& target_type)
			{
				return initialization_sequence(target_type, initializer_type, can_use_user_defined);
			});
	}
}
