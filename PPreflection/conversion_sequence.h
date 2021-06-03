#pragma once
#include <compare>

#include "PP/view_subsequence_compare.hpp"

#include "convertor.h"
#include "cv_qualification_signature.hpp"
#include "dynamic_variable.h"
#include "functions/constructor.h"
#include "functions/function.h"
#include "qualification_conversion.hpp"
#include "types/reference_type.h"

namespace PPreflection
{
	class non_array_object_type;

	enum conversion_sequence_rank : int
	{
		exact_match = 2,
		promotion = 1,
		conversion = 0,
	};

	static constexpr bool partial_ordering_unequal(
		std::partial_ordering po) noexcept
	{
		return po == std::partial_ordering::less ||
			   po == std::partial_ordering::greater;
	}

	class implicit_conversion_sequence;

	class standard_conversion_sequence
	{
		friend implicit_conversion_sequence;

		struct load_conversion
		{
			PP::unique_pointer<PP::pointer_new<implicit_conversion_sequence>>
				argument_conversion;
			const constructor* c;

			constexpr bool operator==(
				const load_conversion& other) const noexcept
			{
				return c == other.c;
			}

			inline dynamic_object operator()(dynamic_reference r) const;
		};

	private:
		const non_array_object_type* type_target_value;
		const referencable_type* type_target_reference;

		load_conversion load;
		convertor_object to_pointer;
		convertor_object promotion_conversion;
		convertor_object function_noexcept;
		convertor_reference derived_to_base_reference_conversion;

		conversion_sequence_rank rank;
		PP::cv_qualifier target_cv;
		bool identity;
		bool load_present;
		bool has_qualification_conversion;
		bool enum_with_fixed_underlying_type;
		bool enum_to_promoted_fixed_type;
		bool converts_pointer_to_bool;
		bool converts_to_base_or_void_pointer;
		bool converts_to_void_pointer;
		bool binds_implicit_parameter_no_ref;
		bool source_lvalue;
		bool target_lvalue;

	private:
		constexpr standard_conversion_sequence(bool source_lvalue) noexcept
			: type_target_value(nullptr)
			, type_target_reference(nullptr)
			, load(nullptr, nullptr)
			, to_pointer(nullptr)
			, promotion_conversion(nullptr)
			, function_noexcept(nullptr)
			, derived_to_base_reference_conversion(nullptr)
			, rank(conversion_sequence_rank::exact_match)
			, target_cv(PP::cv_qualifier::none)
			, identity(false)
			, load_present(false)
			, has_qualification_conversion(false)
			, enum_with_fixed_underlying_type(false)
			, enum_to_promoted_fixed_type(false)
			, converts_pointer_to_bool(false)
			, converts_to_base_or_void_pointer(false)
			, converts_to_void_pointer(false)
			, binds_implicit_parameter_no_ref(false)
			, source_lvalue(source_lvalue)
			, target_lvalue(false)
		{}

	public:
		constexpr standard_conversion_sequence() noexcept
			: standard_conversion_sequence(false)
		{}

		constexpr standard_conversion_sequence(
			const reference_type& source) noexcept
			: standard_conversion_sequence(source.is_lvalue())
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

		constexpr auto get_target_cv() const noexcept
		{
			return (PP::cv_qualifier)target_cv;
		}

		dynamic_reference do_reference_binding(
			dynamic_reference r) const noexcept
		{
			if (derived_to_base_reference_conversion)
				r = derived_to_base_reference_conversion(r);

			if (type_target_reference)
				return r.with_cv_ref(get_target_cv(), target_lvalue);
			else
				return r;
		}

		dynamic_reference convert(
			dynamic_variable v,
			dynamic_variable& temp_variable) const noexcept
		{
			if (load_present || to_pointer || promotion_conversion ||
				function_noexcept || has_qualification_conversion)
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
					temp =
						qualification_conversion(prev_ref, *type_target_value);
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

		constexpr void set_validity(
			const non_array_object_type& new_target_type) noexcept
		{
			type_target_value = &new_target_type;
		}
		constexpr void set_validity(
			cv_type<referencable_type> new_target_cv_type,
			bool is_lvalue) noexcept
		{
			type_target_reference = &new_target_cv_type.type;
			target_lvalue = is_lvalue;
			target_cv = new_target_cv_type.cv;
		}
		constexpr void set_validity(
			const reference_type& new_target_type) noexcept
		{
			set_validity(new_target_type.remove_reference(),
						 new_target_type.is_lvalue());
		}
		constexpr void set_validity(
			cv_type<class_type> new_target_cv_type) noexcept
		{
			set_validity(new_target_cv_type, true);
			binds_implicit_parameter_no_ref = true;
		}

		constexpr void set_load(
			const class_type& target,
			const constructor& c,
			implicit_conversion_sequence argument_conversion) noexcept;
		constexpr void set_load(
			const non_array_object_type& target_non_class) noexcept
		{
			load_present = true;
			load.c = nullptr;
			type_target_value = &target_non_class;
			identity = false;
		}

		constexpr void set_to_pointer(convertor_object convertor) noexcept
		{
			to_pointer = convertor;
		}
		constexpr void set_function_noexcept(
			convertor_object convertor) noexcept
		{
			function_noexcept = convertor;
		}
		constexpr void set_promotion_conversion(
			convertor_object convertor) noexcept
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
		constexpr void set_derived_to_base_reference_conversion(
			convertor_reference convertor) noexcept
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

		constexpr bool same_load(
			const standard_conversion_sequence& other) const noexcept
		{
			return (!load_present && !other.load_present) ||
				   (load_present && other.load_present && load == other.load);
		}

		constexpr bool identical_except_qualification(
			const standard_conversion_sequence& other) const noexcept
		{
			return same_load(other) && to_pointer == other.to_pointer &&
				   promotion_conversion == other.promotion_conversion &&
				   function_noexcept == other.function_noexcept &&
				   derived_to_base_reference_conversion ==
					   other.derived_to_base_reference_conversion &&
				   has_qualification_conversion &&
				   other.has_qualification_conversion;
		}

		struct view_sentinel
		{};

		struct view_iterator
		{
			convertor_object to_pointer;
			convertor_object promotion_conversion;
			convertor_object function_noexcept;
			bool has_qualification_conversion;

			int position;

			constexpr convertor_object operator*()
			{
				switch (position)
				{
					case 0:
						return to_pointer;
					case 1:
						return promotion_conversion;
					case 2:
						return function_noexcept;
					case 3:
						[[fallthrough]];
					default:
						return nullptr;
				}
			}

			constexpr void step()
			{
				switch (position)
				{
					case 0:
						if (promotion_conversion)
						{
							position = 1;
							break;
						}
						else
							[[fallthrough]];
					case 1:
						if (function_noexcept)
						{
							position = 2;
							break;
						}
						else
							[[fallthrough]];
					case 2:
						if (has_qualification_conversion)
						{
							position = 3;
							break;
						}
						else
							[[fallthrough]];
					case 3:
						[[fallthrough]];
					default:
						position = 4;
						break;
				}
			}

			constexpr bool operator==(view_sentinel) const
			{
				return position == 4;
			}

			constexpr auto begin() const
			{
				return *this;
			}
			constexpr auto end() const
			{
				return view_sentinel{};
			}
		};

		constexpr int make_position() const
		{
			if (to_pointer)
				return 0;
			else if (promotion_conversion)
				return 1;
			else if (function_noexcept)
				return 2;
			else if (has_qualification_conversion)
				return 3;
			else
				return 4;
		}

		constexpr auto make_view() const
		{
			return view_iterator(to_pointer,
								 promotion_conversion,
								 function_noexcept,
								 has_qualification_conversion,
								 make_position());
		}

		constexpr std::partial_ordering operator<=>(
			const standard_conversion_sequence& other) const noexcept
		{
			// 3.2.1
			if (auto compare_subsequence =
					PP::view_subsequence_compare(other.make_view(),
												 make_view());
				partial_ordering_unequal(compare_subsequence))
				return compare_subsequence;

			// 3.2.2
			auto compare_subsequence_rank = get_rank() <=> other.get_rank();

			if (compare_subsequence_rank != 0)
				return compare_subsequence_rank;

			// 3.3.4
			else
			{
				// 4.1
				if (auto compare_converts_pointer_to_bool =
						other.converts_pointer_to_bool <=>
						converts_pointer_to_bool;
					compare_converts_pointer_to_bool != 0)
					return compare_converts_pointer_to_bool;

				// 4.2
				if (enum_with_fixed_underlying_type &&
					other.enum_with_fixed_underlying_type)
				{
					auto compare_enum_to_promoted_fixed_type =
						other.enum_to_promoted_fixed_type <=>
						enum_to_promoted_fixed_type;
					if (compare_enum_to_promoted_fixed_type != 0)
						return compare_enum_to_promoted_fixed_type;
				}

				// 4.3
				if (converts_to_base_or_void_pointer &&
					other.converts_to_base_or_void_pointer)
				{
					auto compare_converts_to_void_pointer =
						other.converts_to_void_pointer <=>
						converts_to_void_pointer;
					if (compare_converts_to_void_pointer != 0)
						return compare_converts_to_void_pointer;
				}

				// 4.4
				// TODO
				// Base -> Middle -> Derived
			}

			// 3.2.3
			// slightly modified to:
			// S1 and S2 include reference bindings (9.4.4) and neither refers
			// to an implicit object parameter of a non-static member function
			// declared without a ref-qualifier, and S1 binds an rvalue
			// reference to an rvalue or an lvalue reference to an lvalue and S2
			// binds an lvalue reference to an rvalue or an rvalue reference to
			// an lvalue
			if (type_target_reference && other.type_target_reference &&
				!binds_implicit_parameter_no_ref &&
				!other.binds_implicit_parameter_no_ref)
			{
				auto compare_same_category =
					(source_lvalue == target_lvalue) <=>
					(other.source_lvalue == other.target_lvalue);
				if (compare_same_category != 0)
					return compare_same_category;
			}

			// 3.2.4
			// subsumed by the modified 3.2.3

			// 3.2.5
			if (identical_except_qualification(other))
			{
				auto compare_qualification =
					cv_qualification_signature(*type_target_value) <=>
					cv_qualification_signature(*other.type_target_value);
				if (partial_ordering_unequal(compare_qualification))
					return compare_qualification;
			}

			// 3.2.6
			if (type_target_reference && other.type_target_reference)
			{
				auto compare_cv = other.target_cv <=> target_cv;
				if (compare_cv != 0)
					return compare_cv;
			}

			return std::partial_ordering::unordered;
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
				return conversion->invoke_unsafe(
					PP::make_any_iterator(PP::view_begin(PP::make_array(r))));
			else
				return dynamic_variable::create_invalid(
					dynamic_object::invalid_code::overload_resolution_error);
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

		constexpr bool same_user_defined_function(
			const user_defined_conversion_t& other) const noexcept
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
		static constexpr auto create_standard(
			standard_conversion_sequence sequence) noexcept
		{
			implicit_conversion_sequence s;
			s.first_standard_conversion = PP::move(sequence);
			return s;
		}

		constexpr auto with_user_defined_conversion(
			const function& new_conversion) && noexcept
		{
			auto copy = PP::move(*this);
			copy.user_defined_conversion.set_conversion(new_conversion);
			return copy;
		}
		constexpr auto with_second_standard_conversion(
			standard_conversion_sequence sequence) && noexcept
		{
			auto copy = PP::move(*this);
			copy.second_standard_conversion = PP::move(sequence);
			return copy;
		}

		constexpr void set_reference_bind(
			const reference_type& target_type) noexcept
		{
			if (!user_defined_conversion.present())
				first_standard_conversion.set_validity(target_type);
			else
				second_standard_conversion.set_validity(target_type);
		}

		constexpr std::partial_ordering operator<=>(
			const implicit_conversion_sequence& other) const noexcept
		{
			auto type_this = get_type();
			auto type_other = other.get_type();

			// 2.1
			if (type_this == type::standard && type_other == type::user_defined)
				return std::partial_ordering::greater;
			else if (type_this == type::user_defined &&
					 type_other == type::standard)
				return std::partial_ordering::less;

			// 3.2
			else if (type_this == type::standard &&
					 type_other == type::standard)
				return first_standard_conversion <=>
					   other.first_standard_conversion;

			// 3.3
			else if (type_this == type::user_defined &&
					 type_other == type::user_defined &&
					 user_defined_conversion.same_user_defined_function(
						 other.user_defined_conversion))
				return second_standard_conversion <=>
					   other.second_standard_conversion;

			return std::partial_ordering::unordered;
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

		dynamic_reference convert(dynamic_reference r,
								  dynamic_variable& temp_object) const
		{
			switch (get_type())
			{
				case type::standard:
					return first_standard_conversion.convert(
						dynamic_variable(r),
						temp_object);
				case type::user_defined:
					return second_standard_conversion.convert(
						user_defined_conversion.convert(
							first_standard_conversion.convert(
								dynamic_variable(r),
								temp_object)),
						temp_object);
				case type::invalid:
					[[fallthrough]];
				case type::ambiguous:
					[[fallthrough]];
				default:
					return dynamic_variable::create_invalid(
						dynamic_object::invalid_code::
							overload_resolution_error);
			}
		}
	};
}

PPreflection::dynamic_object
PPreflection::standard_conversion_sequence::load_conversion::operator()(
	dynamic_reference r) const
{
	if (c)
	{
		auto converted_argument = dynamic_variable::create_void();
		auto converted_argument_reference =
			argument_conversion->convert(r, converted_argument);
		return c->invoke_unsafe(
			PP::make_any_iterator(&converted_argument_reference));
	}
	else
		return dynamic_object::create_shallow_copy(r);
}

constexpr void PPreflection::standard_conversion_sequence::set_load(
	const class_type& target,
	const constructor& c,
	implicit_conversion_sequence argument_conversion) noexcept
{
	load_present = true;
	load.argument_conversion =
		PP::make_unique_copy(PP::unique_tag_new, PP::move(argument_conversion));
	load.c = &c;
	type_target_value = &target;
	identity = false;
}
