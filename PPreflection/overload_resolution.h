#pragma once
#include "PP/empty_view.hpp"
#include "PP/optional.hpp"
#include "PP/push_back_iterator.hpp"
#include "PP/small_optimized_vector.hpp"
#include "PP/utility/move.hpp"
#include "PP/vector.hpp"

#include "conversion_sequence.h"

#include <iostream>

namespace PPreflection
{
	inline void pick_viable_candidates(PP::concepts::view auto&& candidates,
	                                   PP::size_t argument_count,
	                                   auto viable_i)
	{
		for (const auto& f : PP_F(candidates) | PP::transform(PP::unref))
		{
			if (PP::view_count(f.parameter_types_olr()) == argument_count)
			{
				*viable_i++ = f;
			}
		}
	}

	template <typename Function>
	class viable_function
	{
		PP::vector<implicit_conversion_sequence> conversion_sequences;
		PP::reference_wrapper<const Function&> f;

	public:
		explicit inline viable_function(const Function& f) noexcept
			: conversion_sequences()
			, f(f)
		{}

		viable_function(viable_function&&) = default;
		viable_function& operator=(viable_function&&) = default;

		inline implicit_conversion_sequence get_first_sequence() const noexcept
		{
			return /*PP::move*/ (implicit_conversion_sequence &&)(
				conversion_sequences[0]);
		}

		inline void make_conversion_sequences(
			PP::concepts::view auto&& argument_types,
			bool can_use_user_defined);

		inline bool has_invalid_conversion() const
		{
			for (auto& s : conversion_sequences)
				if (s.get_type() == implicit_conversion_sequence::type::invalid)
					return true;

			return false;
		}

		inline bool operator>(const viable_function& other) const noexcept
		{
			bool has_worse_sequence = false;
			bool has_better_sequence = false;

			for (auto [my_sequence, other_sequence] :
			     PP::zip_view_pack(conversion_sequences,
			                       other.conversion_sequences))
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

		inline const Function& get_function() const noexcept
		{
			return f;
		}

		dynamic_variable invoke(PP::concepts::view auto&& arguments) const
		{
			PP::small_optimized_vector<dynamic_variable, 8> converted_arguments;
			PP::small_optimized_vector<dynamic_reference, 8>
				converted_argument_references;

			for (auto [sequence, argument] :
			     PP::zip_view_pack(conversion_sequences, PP_F(arguments)))
			{
				converted_arguments.push_back(dynamic_variable::create_void());
				converted_argument_references.push_back(
					sequence.convert(argument, converted_arguments.back()));
			}

			return get_function().invoke_unsafe(PP::make_any_iterator(
				PP::view_begin(converted_argument_references)));
		}
	};

	template <typename Function>
	class viable_function_with_return_sequence
		: public viable_function<Function>
	{
		standard_conversion_sequence return_value_sequence;

	public:
		inline explicit viable_function_with_return_sequence(const Function& f)
			: viable_function<Function>(f)
			, return_value_sequence(
				  standard_conversion_sequence::create_invalid())
		{}

		inline void set_return_value_sequence(
			standard_conversion_sequence sequence) noexcept
		{
			return_value_sequence = PP::move(sequence);
		}

		inline auto make_conversion_sequence() const noexcept
		{
			return this->get_first_sequence()
			    .with_user_defined_conversion(this->get_function())
			    .with_second_standard_conversion(/*PP::move*/ (
					standard_conversion_sequence &&)(return_value_sequence));
		}

		inline bool operator>(
			const viable_function_with_return_sequence& other) const noexcept
		{
			if ((const viable_function<Function>&)*this > other)
				return true;

			// 2.2
			if (return_value_sequence.is_valid() &&
			    other.return_value_sequence.is_valid() &&
			    return_value_sequence > other.return_value_sequence)
				return true;

			return false;
		}
	};

	inline auto pick_best_viable_function(
		PP::concepts::view auto& viable_functions)
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

	template <bool with_return_value_sequences, typename Function>
	using viable_function_type_helper = PP_GT(PP::conditional(
		PP::value<with_return_value_sequences>,
		PP::type<viable_function_with_return_sequence<Function>>,
		PP::type<viable_function<Function>>));

	inline auto overload_resolution(PP::concepts::view auto&& candidates,
	                                PP::concepts::view auto&& argument_types,
	                                auto&& return_value_sequences,
	                                bool can_use_user_defined)
		-> PP::tuple<
			PP::optional<viable_function_type_helper<
				PP::concepts::view<decltype(return_value_sequences)>,
				PP_GT(~PP_DECLTYPE(PP::unref(*PP::view_begin(candidates))))>>,
			overload_resolution_error>
	{
		constexpr bool with_return_value_sequences =
			PP::concepts::view<decltype(return_value_sequences)>;
		using candidate_type =
			PP_GT(~PP_DECLTYPE(PP::unref(*PP::view_begin(candidates))));
		using viable_function_type =
			viable_function_type_helper<with_return_value_sequences,
		                                candidate_type>;

		PP::small_optimized_vector<viable_function_type, 8> viable_functions;

		pick_viable_candidates(PP_F(candidates),
		                       PP::view_count(argument_types),
		                       PP::push_back_iterator(viable_functions));

		if constexpr (with_return_value_sequences)
		{
			for (auto [vf, s] :
			     PP::zip_view_pack(viable_functions, return_value_sequences))
				vf.set_return_value_sequence(PP::move(s));
		}

		for (auto& vf : viable_functions)
			vf.make_conversion_sequences(argument_types, can_use_user_defined);

		viable_functions.remove(
			[](const viable_function_type& vf)
			{
				return vf.has_invalid_conversion();
			});

		auto [winner, is_ambiguous] =
			pick_best_viable_function(viable_functions);

		if (is_ambiguous)
			return PP::make_tuple(PP::nullopt,
			                      overload_resolution_error::ambiguous);
		else if (!winner)
			return PP::make_tuple(PP::nullopt,
			                      overload_resolution_error::invalid);
		else
			return PP::forward_as_tuple(
				PP::make_optional_copy(PP::move(*winner)),
				overload_resolution_error());
	}

	inline implicit_conversion_sequence overload_resolution(
		PP::concepts::view auto&& candidates,
		const reference_type& argument_type,
		PP::concepts::view auto&& return_value_sequences)
	{
		auto [result, error_code] =
			overload_resolution(PP_F(candidates),
		                        PP::forward_as_array(argument_type),
		                        PP_F(return_value_sequences),
		                        false);

		if (result)
			return result->make_conversion_sequence();
		else if (error_code == overload_resolution_error::ambiguous)
			return implicit_conversion_sequence::create_ambiguous();
		else // if (error_code == overload_resolution_error::invalid)
			return implicit_conversion_sequence::create_invalid();
	}

	inline auto overload_resolution(PP::concepts::view auto&& candidates,
	                                PP::concepts::view auto&& argument_types)
	{
		return overload_resolution(PP_F(candidates),
		                           PP_F(argument_types),
		                           nullptr,
		                           true);
	}
}
