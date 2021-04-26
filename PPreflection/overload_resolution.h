#pragma once
#include "PP/empty_view.hpp"
#include "PP/optional.hpp"
#include "PP/push_back_iterator.hpp"
#include "PP/small_optimized_vector.hpp"
#include "PP/utility/move.hpp"

#include "conversion_sequence.h"

namespace PPreflection
{
	constexpr void pick_viable_candidates(PP::concepts::view auto&& candidates, PP::size_t argument_count, auto viable_i)
	{
		for (const function& f : PP_FORWARD(candidates))
		{
			if (PP::view_count(f.parameter_types_olr()) == argument_count)
			{
				*viable_i++ = f;
			}
		}
	}

	class viable_function
	{
		PP::small_optimized_vector<implicit_conversion_sequence, 4> conversion_sequences;
		PP::reference_wrapper<const function&> f;

	protected:
		constexpr implicit_conversion_sequence get_first_sequence() const noexcept
		{
			return (implicit_conversion_sequence&&)(conversion_sequences[0]);
		}

	public:
		explicit constexpr viable_function(const function& f) noexcept
			: conversion_sequences()
			, f(f)
		{}

		viable_function(viable_function&&) = default;
		viable_function& operator=(viable_function&&) = default;

		constexpr void make_conversion_sequences(PP::concepts::view auto&& argument_types, bool can_use_user_defined);

		constexpr bool has_invalid_conversion() const
		{
			for (auto& s : conversion_sequences)
				if (s.get_type() == implicit_conversion_sequence::type::invalid)
					return true;

			return false;
		}

		constexpr bool operator>(const viable_function& other) const noexcept
		{
			bool has_worse_sequence = false;
			bool has_better_sequence = false;

			for (auto [my_sequence, other_sequence] : PP::zip_view_pack(conversion_sequences, other.conversion_sequences))
			{
				auto compare_sequence = my_sequence <=> other_sequence;
				if (compare_sequence < 0)
				{
					has_worse_sequence = true;
					if (has_better_sequence)
						break;
				}
				else if (compare_sequence > 0)
				{
					has_better_sequence = true;
					if (has_worse_sequence)
						break;
				}
			}

			// 2
			if (has_worse_sequence)
				return false;
				
			// 2.1
			if (has_better_sequence)
				return true;

			return false;
		}

		constexpr const function& get_function() const noexcept
		{
			return f;
		}

		dynamic_variable invoke(PP::concepts::view auto&& arguments) const
		{
			PP::small_optimized_vector<dynamic_variable, 8> converted_arguments;
			PP::small_optimized_vector<dynamic_reference, 8> converted_argument_references;

			for (auto [sequence, argument] : PP::zip_view_pack(conversion_sequences, PP_FORWARD(arguments)))
			{
				converted_arguments.push_back(dynamic_variable::create_void());
				converted_argument_references.push_back(sequence.convert(argument, converted_arguments.back()));
			}

			return get_function().invoke_unsafe(PP::make_any_iterator(PP::view_begin(converted_argument_references)));
		}
	};

	class viable_function_with_return_sequence : public viable_function
	{
		standard_conversion_sequence return_value_sequence;

	public:
		constexpr explicit viable_function_with_return_sequence(const function& f)
			: viable_function(f)
			, return_value_sequence(standard_conversion_sequence::create_invalid())
		{}

		constexpr void set_return_value_sequence(standard_conversion_sequence sequence) noexcept
		{
			return_value_sequence = PP::move(sequence);
		}

		constexpr auto make_conversion_sequence() const noexcept
		{
			return get_first_sequence()
				.with_user_defined_conversion(get_function())
				.with_second_standard_conversion((standard_conversion_sequence&&)(return_value_sequence));
		}

		constexpr bool operator>(const viable_function_with_return_sequence& other) const noexcept
		{
			if ((const viable_function&)*this > other)
				return true;

			// 2.2
			if (return_value_sequence.is_valid() && other.return_value_sequence.is_valid() &&
				return_value_sequence > other.return_value_sequence)
				return true;

			return false;
		}
	};

	constexpr auto pick_best_viable_function(PP::concepts::view auto& viable_functions)
	{
		decltype(viable_functions.begin()) winner = nullptr;
		bool ambiguous_winner = false;

		for (auto& vf : viable_functions)
		{
			bool better_than_all_others = true;

			for (auto& other : viable_functions)
			{
				if (&vf == &other)
					continue;
				if (!(vf > other))
				{
					better_than_all_others = false;
					break;
				}
			}

			if (better_than_all_others)
			{
				if (winner)
				{
					ambiguous_winner = true;
					break;
				}
				winner = &vf;
			}
		}

		return PP::make_tuple(winner, ambiguous_winner);
	}

	enum class overload_resolution_error
	{
		invalid,
		ambiguous,
	};

	template <bool with_return_value_sequences>
	using viable_function_type_helper = PP_GET_TYPE(PP::conditional(
		PP::value<with_return_value_sequences>,
		PP::type<viable_function_with_return_sequence>,
		PP::type<viable_function>));

	constexpr auto overload_resolution(
		PP::concepts::view auto&& candidates,
		PP::concepts::view auto&& argument_types,
		auto&& return_value_sequences,
		bool can_use_user_defined) 
			-> PP::tuple<PP::optional<viable_function_type_helper<PP::concepts::view<decltype(return_value_sequences)>>>, overload_resolution_error>
	{
		constexpr bool with_return_value_sequences = PP::concepts::view<decltype(return_value_sequences)>;
		using viable_function_type = viable_function_type_helper<with_return_value_sequences>;

		PP::small_optimized_vector<viable_function_type, 8> viable_functions;

		pick_viable_candidates(PP_FORWARD(candidates), PP::view_count(argument_types), PP::push_back_iterator(viable_functions));

		if constexpr (with_return_value_sequences)
		{
			for (auto [vf, s] : PP::zip_view_pack(viable_functions, return_value_sequences))
				vf.set_return_value_sequence(PP::move(s));
		}

		for (viable_function& vf : viable_functions)
			vf.make_conversion_sequences(argument_types, can_use_user_defined);

		viable_functions.remove([](const viable_function& vf){ return vf.has_invalid_conversion(); });

		auto [winner, is_ambiguous] = pick_best_viable_function(viable_functions);

		if (is_ambiguous)
			return PP::make_tuple(PP::nullopt, overload_resolution_error::ambiguous);
		else if (!winner)
			return PP::make_tuple(PP::nullopt, overload_resolution_error::invalid);
		else
			return PP::forward_as_tuple(PP::make_optional_copy(PP::move(*winner)), overload_resolution_error());
	}

	constexpr implicit_conversion_sequence overload_resolution(
		PP::concepts::view auto&& candidates,
		const reference_type& argument_type,
		PP::concepts::view auto&& return_value_sequences)
	{
		auto [result, error_code] = overload_resolution(PP_FORWARD(candidates), PP::forward_as_array(argument_type), PP_FORWARD(return_value_sequences), false);

		if (result)
			return result->make_conversion_sequence();
		else if (error_code == overload_resolution_error::ambiguous)
			return implicit_conversion_sequence::create_ambiguous();
		else// if (error_code == overload_resolution_error::invalid)
			return implicit_conversion_sequence::create_invalid();
	}

	constexpr auto overload_resolution(
		PP::concepts::view auto&& candidates,
		PP::concepts::view auto&& argument_types)
	{
		return overload_resolution(PP_FORWARD(candidates), PP_FORWARD(argument_types), nullptr, true);
	}
}
