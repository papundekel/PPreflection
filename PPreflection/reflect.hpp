#ifndef PPREFLECTOR_GUARD
#pragma once
#include "reflect.h"

#include "PP/apply_template.hpp"
#include "PP/empty_tuple.hpp"
#include "PP/functional/id.hpp"
#include "PP/template_tuple.hpp"
#include "PP/transform_view.hpp"
#include "PP/tuple_map.hpp"
#include "PP/type_t.hpp"
#include "PP/value_t.hpp"

#include "get_type_class.hpp"
#include "types/implementations/implementations.hpp"

namespace PPreflection
{
	namespace detail
	{
		constexpr inline auto basic_types =
			PP::template_tuple<basic_reference_type,
							   basic_void_type,
							   basic_function_type,
							   basic_unknown_bound_array_type,
							   basic_known_bound_array_type,
							   basic_null_type,
							   arithmetic_type_strong,
							   arithmetic_type_strong,
							   basic_pointer_type,
							   basic_pointer_to_member_type,
							   basic_non_union_class_type,
							   basic_union_type,
							   basic_enum_type>;

		template <PP::constant_string I, typename T>
		constexpr auto metadata = basic_types[PP::value_t_static_cast(
			PP::type_size_t,
			get_type_class_value_t(PP::type<T>))](PP::type<T>)();

		static constexpr auto X() noexcept;

		static constexpr auto& reflect_helper(
			PP::concepts::type auto t) noexcept
		{
			return metadata<X(), PP_GET_TYPE(PP::remove_cv(t))>;
		}

		using namespace PP::literals;

		template <PP::constant_string I>
		constexpr inline auto metadata<I, tags::name<tags::global<I>>> = ""_sv;

		template <PP::constant_string I>
		constexpr inline auto metadata<I, tags::name<float>> = "float"_sv;
		template <PP::constant_string I>
		constexpr inline auto metadata<I, tags::name<double>> = "double"_sv;
		template <PP::constant_string I>
		constexpr inline auto metadata<I, tags::name<long double>> =
			"long double"_sv;
		template <PP::constant_string I>
		constexpr inline auto metadata<I, tags::name<bool>> = "bool"_sv;
		template <PP::constant_string I>
		constexpr inline auto metadata<I, tags::name<char>> = "char"_sv;
		template <PP::constant_string I>
		constexpr inline auto metadata<I, tags::name<signed char>> =
			"signed char"_sv;
		template <PP::constant_string I>
		constexpr inline auto metadata<I, tags::name<unsigned char>> =
			"unsigned char"_sv;
		template <PP::constant_string I>
		constexpr inline auto metadata<I, tags::name<wchar_t>> = "wchar_t"_sv;
		template <PP::constant_string I>
		constexpr inline auto metadata<I, tags::name<short int>> =
			"short int"_sv;
		template <PP::constant_string I>
		constexpr inline auto metadata<I, tags::name<int>> = "int"_sv;
		template <PP::constant_string I>
		constexpr inline auto metadata<I, tags::name<long int>> = "long int"_sv;
		template <PP::constant_string I>
		constexpr inline auto metadata<I, tags::name<long long int>> =
			"long long int"_sv;
		template <PP::constant_string I>
		constexpr inline auto metadata<I, tags::name<unsigned short int>> =
			"unsigned short int"_sv;
		template <PP::constant_string I>
		constexpr inline auto metadata<I, tags::name<unsigned int>> =
			"unsigned int"_sv;
		template <PP::constant_string I>
		constexpr inline auto metadata<I, tags::name<unsigned long int>> =
			"unsigned long int"_sv;
		template <PP::constant_string I>
		constexpr inline auto metadata<I, tags::name<unsigned long long int>> =
			"unsigned long long int"_sv;
#ifdef __cpp_char8_t
		template <PP::constant_string I>
		constexpr inline auto metadata<I, tags::name<char8_t>> = "char8_t"_sv;
#endif
#ifdef __cpp_unicode_characters
		template <PP::constant_string I>
		constexpr inline auto metadata<I, tags::name<char16_t>> = "char16_t"_sv;
		template <PP::constant_string I>
		constexpr inline auto metadata<I, tags::name<char32_t>> = "char32_t"_sv;
#endif

		template <PP::constant_string I, typename Class, typename... Parameters>
		constexpr inline auto
			metadata<I, tags::is_explicit<Class, Parameters...>> =
				PP::value_false;

		template <PP::constant_string I, typename E>
		constexpr inline auto metadata<I, tags::enum_fixed_type<E>> =
			PP::type_void;
	}
}

#endif
