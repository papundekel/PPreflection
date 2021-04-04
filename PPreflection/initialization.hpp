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

	constexpr bool is_rvalue_or_function_lvalue(const reference_type& t) noexcept
	{
		return !t.is_lvalue() || t.remove_reference().type.cast_down().holds_alternative(PP::type<function_type>);
	}

	constexpr bool valid_return_type_for_conversion(PP::concepts::value auto lvalue, const reference_type& return_type) noexcept
	{
		if constexpr (PP_GET_VALUE(lvalue))
			return return_type.is_lvalue();
		else
			return is_rvalue_or_function_lvalue(return_type);
	}

	constexpr standard_conversion_sequence valid_return_type_for_conversion(PP::concepts::value auto lvalue, return_type_reference return_type, const reference_type& target_type) noexcept
	{
		return return_type.visit(PP::overloaded
		(
			[](const non_array_object_type&){ return standard_conversion_sequence::create_invalid(); },
			[lvalue, &target_type](const reference_type& rt)
			{
				standard_conversion_sequence sequence(rt);

				if (valid_return_type_for_conversion(lvalue, rt))
				{
					auto referenced_cv_type_target = target_type.remove_reference();
					auto referenced_cv_type_rt = rt.remove_reference();

					bool same = referenced_cv_type_target.type == referenced_cv_type_rt.type;
					auto [derived, rt_class_ptr, target_class_ptr] = derived_from(referenced_cv_type_rt.type, referenced_cv_type_target.type);

					if ((same || derived) && referenced_cv_type_target >= referenced_cv_type_rt)
					{
						sequence.set_validity(target_type);
						if (derived)
							sequence.set_derived_to_base_reference_conversion(rt_class_ptr->base_reference_conversion(*target_class_ptr));
					}
				}

				return sequence;
			},
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

	constexpr void push_conversion_candidates(
		PP::concepts::value auto lvalue,
		const reference_type& target_type,
		const referencable_type& initializer_type,
		auto& candidates,
		auto& return_value_sequences)
	{
		const auto* initializer_class_ptr = dynamic_cast<const class_type*>(&initializer_type);
		if (!initializer_class_ptr)
			return;

		const auto& initializer_class = *initializer_class_ptr;

		PP::simple_vector<PP::reference_wrapper<const conversion_function&>> conversion_functions;
		initializer_class.get_conversion_functions_inherited(PP::push_back_iterator(conversion_functions));

		for (const conversion_function& cf : conversion_functions)
		{
			auto sequence = valid_return_type_for_conversion(lvalue, cf.return_type(), target_type);

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

	constexpr implicit_conversion_sequence initialization_sequence(const reference_type& target_type, const reference_type& initializer_type, bool can_use_user_defined)
	{
		auto sequence = implicit_conversion_sequence::create_invalid();

		auto referenced_target_cv_type = target_type.remove_reference();
		auto referenced_initializer_cv_type = initializer_type.remove_reference();

		bool same = referenced_target_cv_type.type == referenced_initializer_cv_type.type;
		auto [derived, initializer_class_ptr, target_class_ptr] = derived_from(referenced_initializer_cv_type.type, referenced_target_cv_type.type);

		if (target_type.is_lvalue())
		{
			if (initializer_type.is_lvalue() && (same || derived) && referenced_target_cv_type >= referenced_initializer_cv_type)
			{
				standard_conversion_sequence standard_sequence(initializer_type);

				standard_sequence.set_validity(target_type);
				if (derived)
					standard_sequence.set_derived_to_base_reference_conversion(initializer_class_ptr->base_reference_conversion(*target_class_ptr));

				sequence = implicit_conversion_sequence::create_standard(standard_sequence);
			}
			else if (can_use_user_defined && !same && !derived)
			{
				PP::simple_vector<PP::reference_wrapper<const function&>> candidates(4);
				PP::simple_vector<standard_conversion_sequence> return_value_sequences(4);
				push_conversion_candidates(PP::value_true, target_type, referenced_initializer_cv_type.type, candidates, return_value_sequences);

				sequence = overload_resolution(candidates, initializer_type, return_value_sequences);
			}
		}
		
		if (!sequence.is_valid() && ((target_type.is_lvalue() && referenced_target_cv_type.cv == PP::cv_qualifier::Const) || !target_type.is_lvalue()))
		{
			if (is_rvalue_or_function_lvalue(target_type) && (same || derived) && referenced_target_cv_type >= referenced_initializer_cv_type)
			{
				standard_conversion_sequence standard_sequence(initializer_type);

				standard_sequence.set_validity(target_type);
				if (derived)
					standard_sequence.set_derived_to_base_reference_conversion(initializer_class_ptr->base_reference_conversion(*target_class_ptr));

				sequence = implicit_conversion_sequence::create_standard(standard_sequence);
			}
			else if (can_use_user_defined && !same && !derived)
			{
				PP::simple_vector<PP::reference_wrapper<const function&>> candidates(4);
				PP::simple_vector<standard_conversion_sequence> return_value_sequences(4);
				push_conversion_candidates(PP::value_false, target_type, referenced_initializer_cv_type.type, candidates, return_value_sequences);

				sequence = overload_resolution(candidates, initializer_type, return_value_sequences);
			}

			if (!sequence.is_valid())
			{
				const auto* referenced_target_object_ptr = dynamic_cast<const non_array_object_type*>(&referenced_target_cv_type.type);
				if (referenced_target_object_ptr)
				{
					sequence = initialization_sequence(*referenced_target_object_ptr, initializer_type, can_use_user_defined);
					sequence.set_reference_bind(target_type);
				}
			}
		}

		return sequence;
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
