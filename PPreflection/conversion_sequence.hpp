#pragma once
#include "PP/type_disjunction_reference.hpp"

#include "convertor.h"
#include "dynamic_variable.h"
#include "functions/conversion_function.h"
#include "functions/one_parameter_converting_constructor.h"
#include "types/non_array_object_type.h"
#include "types/parameter_type_reference.h"
#include "types/reference_type.h"

namespace PPreflection
{
	enum class conversion_sequence_rank : int
	{
		exact_match,
		promotion,
		conversion,
	};

	constexpr bool operator==(conversion_sequence_rank a, conversion_sequence_rank b)
	{
		return (int)a == (int)b;
	}
	constexpr bool operator>(conversion_sequence_rank a, conversion_sequence_rank b)
	{
		return (int)a < (int)b;
	}

	class standard_conversion_sequence
	{
		struct load_conversion
		{
			const class_type* c;
			bool is_present = false;

			constexpr operator bool() const noexcept
			{
				return is_present;
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

		const type* type_source;
		const type* type_target;
		load_conversion load;
		convertor_object to_pointer;
		convertor_object promotion_conversion;
		convertor_object function_noexcept;
		dynamic_reference(*derived_to_base_binder)(dynamic_reference, const class_type&);
		dynamic_reference(*reference_binder)(dynamic_reference, PP::cv_qualifier, bool);
		conversion_sequence_rank rank;
		bool has_qualification_conversion;
		bool enum_has_fixed_undrlying_type;
		bool enum_to_promoted_fixed_type;

		constexpr standard_conversion_sequence(const type* source) noexcept
			: type_source(source)
			, type_target(nullptr)
			, load()
			, to_pointer(nullptr)
			, promotion_conversion(nullptr)
			, function_noexcept(nullptr)
			, rank(conversion_sequence_rank::exact_match)
			, has_qualification_conversion(false)
			, enum_has_fixed_undrlying_type(false)
			, enum_to_promoted_fixed_type(false)
		{}

	public:
		constexpr standard_conversion_sequence() noexcept
			: standard_conversion_sequence(nullptr)
		{}
		constexpr standard_conversion_sequence(const type& source) noexcept
			: standard_conversion_sequence(&source)
		{}

		static constexpr standard_conversion_sequence create_identity(const type& t) noexcept
		{
			standard_conversion_sequence sequence(t);
			sequence.set_validity(t);
			return sequence;
		}

		dynamic_variable convert(dynamic_variable v) const
		{
			if (*type_source != *type_target)
			{
				throw 0;
			}
			else
				return PP::move(v);
		}

		constexpr void set_rank(conversion_sequence_rank new_rank) noexcept
		{
			rank = new_rank;
		}
		constexpr void set_validity(const type& new_target_type) noexcept
		{
			type_target = &new_target_type;
		}
		constexpr void reset_validity() noexcept
		{
			type_target = nullptr;
		}
		constexpr void set_load(const class_type* c) noexcept
		{
			load.is_present = true;
			load.c = c;
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
		constexpr void set_enum_fixed_type() noexcept
		{
			enum_has_fixed_undrlying_type = true;
		}
		constexpr void set_enum_promoted_fixed_type() noexcept
		{
			enum_to_promoted_fixed_type = true;
		}

		constexpr conversion_sequence_rank get_rank() const noexcept
		{
			return rank;
		}

		constexpr bool operator>(const standard_conversion_sequence& other) const noexcept
		{
			auto rank_this = get_rank();
			auto rank_other = other.get_rank();

			if (rank_this != rank_other)
				return rank_this > rank_other;
			else
			{
				return false;
			}
		}
	};

	class implicit_conversion_sequence
	{
		class user_defined_conversion_t
		{
			friend class implicit_conversion_sequence;

			static constexpr struct no_user_defined_conversion_t{} no_user_defined_conversion{};

			PP::type_disjunction_reference<one_parameter_converting_constructor, conversion_function, no_user_defined_conversion_t> conversion;

		public:
			constexpr user_defined_conversion_t() noexcept
				: conversion(no_user_defined_conversion)
			{}

			dynamic_variable convert(dynamic_reference r) const
			{
				return conversion.visit(PP::overloaded
				(
					[r](const auto& c) { return dynamic_variable(c.invoke(r)); },
					[](const no_user_defined_conversion_t&) { return dynamic_variable::create_invalid(dynamic_object::invalid_code::overload_resolution_error); }
				));
			}

			constexpr bool present() const
			{
				return conversion.holds_alternative(PP::type<no_user_defined_conversion_t>);
			}

			constexpr bool same_user_defined_function(const user_defined_conversion_t& other) const noexcept
			{
				return conversion.visit([&other]
					(const auto& c)
					{
						return other.conversion.visit(
							[&c]
							(const auto& c_other)
							{
								if constexpr (PP_DECLTYPE(c) == PP_DECLTYPE(c_other))
									return &c == &c_other;
								else
									return false;
							});
					});
			}
		};

		standard_conversion_sequence first_standard_conversion;
		user_defined_conversion_t user_defined_conversion;
		standard_conversion_sequence second_standard_conversion;
		bool ambiguous;
		bool valid;

	public:
		enum class type
		{
			invalid,
			standard,
			user_defined,
			ambiguous,
		};

		constexpr implicit_conversion_sequence()
			: first_standard_conversion()
			, user_defined_conversion()
			, second_standard_conversion()
			, ambiguous(false)
			, valid(false)
		{}

		static constexpr implicit_conversion_sequence create_invalid() noexcept
		{
			return implicit_conversion_sequence();
		}

		static constexpr implicit_conversion_sequence create_standard(standard_conversion_sequence sequence) noexcept
		{
			implicit_conversion_sequence s;
			s.first_standard_conversion = sequence;
			s.valid = sequence.type_target != nullptr;
			return s;
		}

		constexpr bool operator>(const implicit_conversion_sequence& other) const
		{
			auto type_other = other.get_type();

			switch (get_type())
			{
			case type::invalid:
				return false;
			case type::standard:
				return type_other != type::standard || first_standard_conversion > other.first_standard_conversion;
			case type::user_defined:
				return
					type_other == type::user_defined &&
					user_defined_conversion.same_user_defined_function(other.user_defined_conversion) &&
					second_standard_conversion > other.second_standard_conversion;
			case type::ambiguous:
				return false;
			default:
				return false;
			}
		}

		constexpr type get_type() const
		{
			if (!valid)
				return type::invalid;

			if (ambiguous)
				return type::ambiguous;

			if (!user_defined_conversion.present())
				return type::standard;

			return type::user_defined;
		}

		dynamic_variable convert(dynamic_reference r) const
		{
			auto v = first_standard_conversion.convert(dynamic_variable(r));

			if (user_defined_conversion.present())
			{
				auto v2 = user_defined_conversion.convert(v);
				return second_standard_conversion.convert(PP::move(v2));
			}
			else
			{
				return PP::move(v);
			}
		}

		standard_conversion_sequence& get_first_standard() noexcept
		{
			return first_standard_conversion;
		}
		standard_conversion_sequence& get_second_standard() noexcept
		{
			return second_standard_conversion;
		}
	};
}
