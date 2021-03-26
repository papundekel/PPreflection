#pragma once
#include <optional>

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

	class viable_function_t
	{
		PP::simple_vector<implicit_conversion_sequence> conversion_sequences;
		PP::reference_wrapper<const function&> f;

	public:
		explicit viable_function_t(const function& f) noexcept
			: conversion_sequences(PP::view_count(f.parameter_types()))
			, f(f)
		{}

		constexpr void make_conversion_sequences(PP::concepts::view auto&& argument_types)
		{
			auto parameter_types = f.get().parameter_types();
			auto parameter_types_i = parameter_types.begin();

			for (const reference_type& from_type : PP_FORWARD(argument_types))
			{
				conversion_sequences.push_back(from_type, *parameter_types_i);

				++parameter_types_i;
			}
		}

		constexpr bool has_invalid_conversion() const
		{
			for (auto& s : conversion_sequences)
				if (s.get_type() == implicit_conversion_sequence::type::invalid)
					return true;

			return false;
		}

		constexpr bool has_worse_conversion(const viable_function_t& other) const noexcept
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

		constexpr bool has_better_conversion(const viable_function_t& other) const noexcept
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

		constexpr bool operator>(const viable_function_t& other) const noexcept
		{
			return !has_worse_conversion(other) &&
			(
				has_better_conversion(other) ||
				false
			);
		}

		dynamic_variable invoke(PP::concepts::view auto&& arguments)
		{
			PP::simple_vector<dynamic_variable> converted_arguments;

			for (auto [sequence, argument] : PP::zip_view_pack(conversion_sequences, PP_FORWARD(arguments)))
				converted_arguments.push_back(sequence.convert(argument));

			PP::simple_vector<dynamic_reference> converted_argument_references;
			for (auto& v : converted_arguments)
				converted_argument_references.push_back(v);

			return f.get().invoke_unsafe(PP::make_any_iterator(PP::view_begin(converted_argument_references)));
		}
	};

	constexpr auto pick_best_viable_function(PP::concepts::view auto& viable_functions)
	{
		viable_function_t* winner = nullptr;
		bool ambiguous_winner = false;

		for (viable_function_t& vf : viable_functions)
		{
			bool better_than_all_others = true;

			for (viable_function_t& other : viable_functions)
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

	constexpr std::optional<viable_function_t> overload_resolution(PP::concepts::view auto&& candidates, PP::concepts::view auto&& arguments)
	{
		auto argument_types = args_to_types(PP_FORWARD(arguments));

		PP::simple_vector<viable_function_t> viable_functions;

		pick_viable_candidates(PP_FORWARD(candidates), PP::view_count(argument_types), PP::push_back_iterator(viable_functions));

		for (auto& vf : viable_functions)
			vf.make_conversion_sequences(argument_types);

		viable_functions.remove([](const viable_function_t& vf){ return vf.has_invalid_conversion(); });

		auto [winner, is_ambiguous] = pick_best_viable_function(viable_functions);

		if (is_ambiguous || !winner)
			return std::nullopt;
		else
			return PP::move(*winner);
	}
}
