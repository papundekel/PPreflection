#pragma once
#include "PP/type_disjunction_reference.hpp"

#include "convertor.h"
#include "cv_qualification_signature.hpp"
#include "dynamic_variable.h"
#include "functions/conversion_function.h"
#include "functions/one_parameter_converting_constructor.h"
#include "qualification_conversion.hpp"
#include "types/non_array_object_type.h"
#include "types/parameter_type_reference.h"
#include "types/reference_type.h"

namespace PPreflection
{
	enum conversion_sequence_rank : unsigned int
	{
		exact_match = 2,
		promotion = 1,
		conversion = 0,
	};

	class standard_conversion_sequence
	{
		struct load_conversion
		{
			const class_type* c;

			constexpr bool operator==(const load_conversion& other) const noexcept
			{
				return c == other.c;
			}

			dynamic_object operator()(dynamic_reference r) const
			{
				if (c)
					return c->copy_initialize_same_or_derived(r);
				else
					return dynamic_object::create_shallow_copy(r);
			}
		};

		friend class implicit_conversion_sequence;

	private:
		const type* type_source;
		const non_array_object_type* type_target_value;
		const reference_type* type_target_reference;

		load_conversion load;
		convertor_object to_pointer;
		convertor_object promotion_conversion;
		convertor_object function_noexcept;
		convertor_reference derived_to_base_reference_conversion;

		unsigned int
			rank : 2,
			identity : 1,
			load_present : 1,
			has_qualification_conversion : 1,
			enum_with_fixed_underlying_type : 1,
			enum_to_promoted_fixed_type : 1,
			converts_pointer_to_bool : 1,
			converts_to_base_or_void_pointer : 1,
			converts_to_void_pointer : 1;

	private:
		constexpr standard_conversion_sequence(const type* source) noexcept
			: type_source(source)
			, type_target_value(nullptr)
			, type_target_reference(nullptr)
			, load(nullptr)
			, to_pointer(nullptr)
			, promotion_conversion(nullptr)
			, function_noexcept(nullptr)
			, derived_to_base_reference_conversion(nullptr)
			, rank(conversion_sequence_rank::exact_match)
			, identity(false)
			, load_present(false)
			, has_qualification_conversion(false)
			, enum_with_fixed_underlying_type(false)
			, enum_to_promoted_fixed_type(false)
			, converts_pointer_to_bool(false)
			, converts_to_base_or_void_pointer(false)
			, converts_to_void_pointer(false)
		{}

		constexpr standard_conversion_sequence() noexcept
			: standard_conversion_sequence(nullptr)
		{}

	public:
		constexpr standard_conversion_sequence(const type& source) noexcept
			: standard_conversion_sequence(&source)
		{}

		static constexpr standard_conversion_sequence create_invalid() noexcept
		{
			return standard_conversion_sequence();
		}
		static constexpr standard_conversion_sequence create_identity() noexcept
		{
			standard_conversion_sequence sequence;
			sequence.identity = true;
			return sequence;
		}
		static constexpr standard_conversion_sequence create_load(const auto& target) noexcept
		{
			standard_conversion_sequence sequence;
			sequence.set_load(target);
			return sequence;
		}

		dynamic_reference do_reference_binding(dynamic_reference r) const noexcept
		{
			if (derived_to_base_reference_conversion)
				r = derived_to_base_reference_conversion(r);
			return r.with_cv_ref(type_target_reference->remove_reference().cv, type_target_reference->is_lvalue());
		}

		dynamic_reference convert(dynamic_variable v, dynamic_variable& temp_variable) const noexcept
		{
			if (load_present || to_pointer || promotion_conversion || function_noexcept || has_qualification_conversion)
			{
				auto temp = dynamic_object::create_void();

				dynamic_reference prev_ref = v.move();

				if (load_present)
				{
					temp = load(v);
					prev_ref = temp.move();
				}
				if (to_pointer)
				{
					temp = to_pointer(prev_ref);
					prev_ref = temp.move();
				}
				if (promotion_conversion)
				{
					temp = promotion_conversion(prev_ref);
					prev_ref = temp.move();
				}
				if (function_noexcept)
				{
					temp = function_noexcept(prev_ref);
					prev_ref = temp.move();
				}
				if (has_qualification_conversion)
				{
					temp = qualification_conversion(prev_ref, *type_target_value);
				}

				temp_variable = dynamic_variable(PP::move(temp));
			}
			else
			{
				temp_variable = PP::move(v);
			}

			return do_reference_binding(temp_variable.move());
		}

		constexpr void set_rank(conversion_sequence_rank new_rank) noexcept
		{
			rank = new_rank;
		}
		constexpr void set_validity(const non_array_object_type& new_target_type) noexcept
		{
			type_target_value = &new_target_type;
		}
		constexpr void set_validity(const reference_type& new_target_type) noexcept
		{
			type_target_reference = &new_target_type;
		}
		constexpr void set_load(const class_type& target) noexcept
		{
			load_present = true;
			load.c = &target;
			type_target_value = &target;
			identity = false;
		}
		constexpr void set_load(const non_array_object_type& target) noexcept
		{
			load_present = true;
			load.c = nullptr;
			type_target_value = &target;
			identity = false;
		}
		constexpr void set_to_pointer(convertor_object convertor) noexcept
		{
			to_pointer = convertor;
		}
		constexpr void set_function_noexcept(convertor_object convertor) noexcept
		{
			function_noexcept = convertor;
		}
		constexpr void set_promotion_conversion(convertor_object convertor) noexcept
		{
			promotion_conversion = convertor;
		}
		constexpr void set_qualification() noexcept
		{
			has_qualification_conversion = true;
		}
		constexpr void set_enum_to_fixed_type() noexcept
		{
			enum_with_fixed_underlying_type = true;
		}
		constexpr void set_enum_to_promoted_fixed_type() noexcept
		{
			enum_with_fixed_underlying_type = true;
			enum_to_promoted_fixed_type = true;
		}
		constexpr void set_converts_pointer_to_bool() noexcept
		{
			converts_pointer_to_bool = true;
		}
		constexpr void set_converts_to_base_pointer() noexcept
		{
			converts_to_base_or_void_pointer = true;
		}
		constexpr void set_converts_to_void_pointer() noexcept
		{
			converts_to_base_or_void_pointer = true;
			converts_to_void_pointer = true;
		}
		constexpr void set_derived_to_base_reference_conversion(convertor_reference convertor) noexcept
		{
			derived_to_base_reference_conversion = convertor;
			rank = conversion_sequence_rank::conversion;
		}

		constexpr auto get_rank() const noexcept
		{
			return conversion_sequence_rank(rank);
		}

		constexpr bool is_identity() const noexcept
		{
			return identity;
		}

		constexpr bool is_valid() const noexcept
		{
			return is_identity() || type_target_value || type_target_reference;
		}

		constexpr bool same_load(const standard_conversion_sequence& other) const noexcept
		{
			return (!load_present && !other.load_present) || (load_present && other.load_present && load == other.load);
		}

		constexpr bool identical_except_qualification(const standard_conversion_sequence& other) const noexcept
		{
			return
				same_load(other) &&
				to_pointer == other.to_pointer &&
				promotion_conversion ==	other.promotion_conversion &&
				function_noexcept == other.function_noexcept &&
				derived_to_base_reference_conversion == other.derived_to_base_reference_conversion &&
				has_qualification_conversion && other.has_qualification_conversion &&
				*type_target_value != *other.type_target_value;
		}

		constexpr bool operator>(const standard_conversion_sequence& other) const noexcept
		{
			auto rank_this = get_rank();
			auto rank_other = other.get_rank();

			// 3.2.1
			// UNIMPLEMENTED
			// proper subsequence

			// 3.2.2
			if (rank_this > rank_other)
				return true;

			// 3.3.4
			if (rank_this == rank_other)
			{
				// 4.1
				if (!converts_pointer_to_bool && other.converts_pointer_to_bool)
					return true;

				// 4.2
				if (enum_with_fixed_underlying_type && other.enum_with_fixed_underlying_type &&
					!enum_to_promoted_fixed_type && other.enum_to_promoted_fixed_type)
					return true;

				// 4.3
				if (converts_to_base_or_void_pointer && other.converts_to_base_or_void_pointer &&
					!converts_to_void_pointer && other.converts_to_void_pointer)
					return true;

				// 4.4
				// UNIMPLEMENTED
				// Base -> Middle -> Derived
			}

			// 3.2.3
			// UNIMPLEMENTED
			// binding to rvalue > binding to lvalue

			// 3.2.4
			// UNIMPLEMENTED
			// binding lvalue function to rvalue > binding lvalue function to lvalue

			// 3.2.5
			if (identical_except_qualification(other) &&
				cv_qualification_signature(*type_target_value).compatible(cv_qualification_signature(*other.type_target_value)))
				return true;

			// 3.2.6
			// UNIMPLEMENTED
			// prefer binding to less cv-qualified reference

			return false;
		}
	};

	class user_defined_conversion_t
	{
		friend class implicit_conversion_sequence;

		const function* conversion;
		bool ambiguous;

	public:
		constexpr user_defined_conversion_t() noexcept
			: conversion(nullptr)
			, ambiguous(false)
		{}

		dynamic_variable convert(dynamic_reference r) const
		{
			if (conversion)
			{
				auto temp = PP::make_array(r);
				auto i = PP::make_any_iterator(PP::view_begin(temp));
				return conversion->invoke_unsafe(i);
			}
			else
				return dynamic_variable::create_invalid(dynamic_object::invalid_code::overload_resolution_error);
		}

		constexpr bool is_ambiguous() const noexcept
		{
			return ambiguous;
		}

		constexpr bool present() const noexcept
		{
			return conversion != nullptr;
		}

		constexpr void set_conversion(const function& new_conversion) noexcept
		{
			conversion = &new_conversion;
		}


		constexpr bool same_user_defined_function(const user_defined_conversion_t& other) const noexcept
		{
			return &conversion == &other.conversion;
		}
	};

	class implicit_conversion_sequence
	{
		standard_conversion_sequence first_standard_conversion;
		user_defined_conversion_t user_defined_conversion;
		standard_conversion_sequence second_standard_conversion;

		constexpr implicit_conversion_sequence()
			: first_standard_conversion()
			, user_defined_conversion()
			, second_standard_conversion()
		{}

	public:
		enum class type
		{
			invalid,
			standard,
			user_defined,
			ambiguous,
		};

		static constexpr auto create_invalid() noexcept
		{
			return implicit_conversion_sequence();
		}
		static constexpr auto create_ambiguous() noexcept
		{
			implicit_conversion_sequence s;
			s.user_defined_conversion.ambiguous = true;
			return s;
		}
		static constexpr auto create_standard(standard_conversion_sequence sequence) noexcept
		{
			implicit_conversion_sequence s;
			s.first_standard_conversion = sequence;
			return s;
		}

		constexpr auto with_first_standard_conversion(standard_conversion_sequence sequence) const noexcept
		{
			auto copy = *this;
			copy.first_standard_conversion = sequence;
			return copy;
		}
		constexpr auto with_user_defined_conversion(const function& new_conversion) const noexcept
		{
			auto copy = *this;
			copy.user_defined_conversion.set_conversion(new_conversion);
			return copy;
		}
		constexpr auto with_second_standard_conversion(standard_conversion_sequence sequence) const noexcept
		{
			auto copy = *this;
			copy.second_standard_conversion = sequence;
			return copy;
		}

		constexpr void set_reference_bind(const reference_type& target_type) noexcept
		{
			if (!user_defined_conversion.present())
				first_standard_conversion.type_target_reference = &target_type;
			else
				second_standard_conversion.type_target_reference = &target_type;
		}

		constexpr bool operator>(const implicit_conversion_sequence& other) const noexcept
		{
			auto type_this = get_type();
			auto type_other = other.get_type();

			// 2.1
			if (type_this == type::standard && type_other == type::user_defined)
				return true;

			// 3.2
			if (type_this == type::standard && type_other == type::standard &&
				first_standard_conversion > other.first_standard_conversion)
				return true;

			// 3.3
			if (type_this == type::user_defined && type_other == type::user_defined &&
				user_defined_conversion.same_user_defined_function(other.user_defined_conversion) &&
				second_standard_conversion > other.second_standard_conversion)
				return true;

			return false;
		}

		constexpr bool is_valid() const noexcept
		{
			return first_standard_conversion.is_valid();
		}

		constexpr type get_type() const noexcept
		{
			if (!first_standard_conversion.is_valid())
				return type::invalid;

			if (user_defined_conversion.is_ambiguous())
				return type::ambiguous;

			if (!user_defined_conversion.present())
				return type::standard;

			return type::user_defined;
		}

		dynamic_reference convert(dynamic_reference r, dynamic_variable& temp_object) const
		{
			switch (get_type())
			{
			case type::standard:
				return first_standard_conversion.convert(dynamic_variable(r), temp_object);
			case type::user_defined:
				return
					second_standard_conversion.convert(
					user_defined_conversion.convert(
					first_standard_conversion.convert(
						dynamic_variable(r), temp_object)), temp_object);
			case type::invalid:
				[[fallthrough]];
			case type::ambiguous:
				[[fallthrough]];
			default:
				return dynamic_variable::create_invalid(dynamic_object::invalid_code::overload_resolution_error);
			}
		}
	};
}
