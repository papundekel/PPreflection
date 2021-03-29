#pragma once
#include <optional>

#include "PP/optional.hpp"
#include "PP/push_back_iterator.hpp"

#include "args_to_types.hpp"
#include "conversion_sequence.hpp"

namespace PPreflection
{
	constexpr void pick_viable_candidates(PP::concepts::view auto&& candidates, PP::size_t argument_count, auto viable_i)
	{
		for (const function& f : PP_FORWARD(candidates))
		{
			if (PP::view_count(f.parameter_types()) == argument_count)
			{
				*viable_i++ = f;
			}
		}
	}

	class viable_function
	{
		PP::simple_vector<implicit_conversion_sequence> conversion_sequences;
		standard_conversion_sequence return_value_sequence;
		PP::reference_wrapper<const function&> f;

	public:
		explicit viable_function(const function& f) noexcept
			: conversion_sequences(PP::view_count(f.parameter_types()))
			, return_value_sequence(standard_conversion_sequence::create_invalid())
			, f(f)
		{}

		viable_function(viable_function&&) = default;
		viable_function& operator=(viable_function&&) = default;

		constexpr void make_conversion_sequences(PP::concepts::view auto&& argument_types, bool can_use_user_defined);

		constexpr void set_return_value_sequence(standard_conversion_sequence sequence) noexcept
		{
			return_value_sequence = sequence;
		}

		constexpr bool has_invalid_conversion() const
		{
			for (auto& s : conversion_sequences)
				if (s.get_type() == implicit_conversion_sequence::type::invalid)
					return true;

			return false;
		}

		constexpr bool has_worse_conversion(const viable_function& other) const noexcept
		{
			bool exists_worse_conversion = false;

			for (auto [my_sequence, other_sequence] : PP::zip_view_pack(conversion_sequences, other.conversion_sequences))
			{
				if (other_sequence > my_sequence)
				{
					exists_worse_conversion = true;
					break;
				}
			}

			return exists_worse_conversion;
		}

		constexpr bool has_better_conversion(const viable_function& other) const noexcept
		{
			bool exists_better_conversion = false;

			for (auto [my_sequence, other_sequence] : PP::zip_view_pack(conversion_sequences, other.conversion_sequences))
			{
				if (my_sequence > other_sequence)
				{
					exists_better_conversion = true;
					break;
				}
			}

			return exists_better_conversion;
		}

		constexpr bool operator>(const viable_function& other) const noexcept
		{
			return !has_worse_conversion(other) &&
			(
				has_better_conversion(other) ||
				false
			);
		}

		const function& get_function() const noexcept
		{
			return f;
		}

		implicit_conversion_sequence make_conversion_sequence() const noexcept
		{
			return conversion_sequences[0]
				.with_user_defined_conversion(get_function())
				.with_second_standard_conversion(return_value_sequence);
		}

		dynamic_variable invoke(PP::concepts::view auto&& arguments)
		{
			PP::simple_vector<dynamic_variable> converted_arguments;
			PP::simple_vector<dynamic_reference> converted_argument_references;

			for (auto [sequence, argument] : PP::zip_view_pack(conversion_sequences, PP_FORWARD(arguments)))
			{
				converted_arguments.push_back(dynamic_variable::create_void());
				converted_argument_references.push_back(sequence.convert(argument, converted_arguments.back()));
			}

			return get_function().invoke_unsafe(PP::make_any_iterator(PP::view_begin(converted_argument_references)));
		}
	};

	constexpr auto pick_best_viable_function(PP::concepts::view auto& viable_functions)
	{
		viable_function* winner = nullptr;
		bool ambiguous_winner = false;

		for (viable_function& vf : viable_functions)
		{
			bool better_than_all_others = true;

			for (viable_function& other : viable_functions)
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
					ambiguous_winner = true;
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

	constexpr PP::tuple<PP::optional<viable_function>, overload_resolution_error> overload_resolution(
		PP::concepts::view auto&& candidates,
		PP::concepts::view auto&& argument_types,
		PP::concepts::view auto&& return_value_sequences,
		bool can_use_user_defined)
	{
		PP::simple_vector<viable_function> viable_functions;

		pick_viable_candidates(PP_FORWARD(candidates), PP::view_count(argument_types), PP::push_back_iterator(viable_functions));

		if (!PP::view_empty(return_value_sequences))
		{
			for (auto [vf, s] : PP::zip_view_pack(viable_functions, return_value_sequences))
				vf.set_return_value_sequence(s);
		}

		for (auto& vf : viable_functions)
			vf.make_conversion_sequences(argument_types, can_use_user_defined);

		viable_functions.remove([](const viable_function& vf){ return vf.has_invalid_conversion(); });

		auto [winner, is_ambiguous] = pick_best_viable_function(viable_functions);

		if (is_ambiguous)
			return PP::make_tuple(PP::nullopt, overload_resolution_error::ambiguous);
		else if (!winner)
			return PP::make_tuple(PP::nullopt, overload_resolution_error::invalid);
		else
			return PP::forward_as_tuple(PP::move(*winner), overload_resolution_error());
	}
}
