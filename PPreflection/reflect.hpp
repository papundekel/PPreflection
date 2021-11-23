#ifndef PPREFLECTOR_GUARD
#pragma once
#include "reflect.h"

#include "PP/always_false.hpp"
#include "PP/apply_template.hpp"
#include "PP/empty_tuple.hpp"
#include "PP/id.hpp"
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

		template <typename T>
		struct unreflected_entity_error
		{
			static_assert(PP::always_false<T>, "unreflected entity");
		};

		template <typename T>
		constexpr inline auto metadata = unreflected_entity_error<T>{};

		template <typename T>
		constexpr inline auto metadata<tags::descriptor<T>> =
			basic_types[PP::value_t_static_cast(
				PP::type_size_t,
				get_type_class_value_t(PP::type<T>))](PP::type<T>)();

		static constexpr auto& reflect_helper(
			PP::concepts::type auto t) noexcept
		{
			return metadata<PP_GT(PP::remove_cv(t))>;
		}

		using namespace PP::literals;

		template <>
		constexpr inline auto metadata<tags::name<tags::global>> = ""_sv;

		template <>
		constexpr inline auto metadata<tags::name<float>> = "float"_sv;
		template <>
		constexpr inline auto metadata<tags::name<double>> = "double"_sv;
		template <>
		constexpr inline auto metadata<tags::name<long double>> =
			"long double"_sv;
		template <>
		constexpr inline auto metadata<tags::name<bool>> = "bool"_sv;
		template <>
		constexpr inline auto metadata<tags::name<char>> = "char"_sv;
		template <>
		constexpr inline auto metadata<tags::name<signed char>> =
			"signed char"_sv;
		template <>
		constexpr inline auto metadata<tags::name<unsigned char>> =
			"unsigned char"_sv;
		template <>
		constexpr inline auto metadata<tags::name<wchar_t>> = "wchar_t"_sv;
		template <>
		constexpr inline auto metadata<tags::name<short int>> = "short int"_sv;
		template <>
		constexpr inline auto metadata<tags::name<int>> = "int"_sv;
		template <>
		constexpr inline auto metadata<tags::name<long int>> = "long int"_sv;
		template <>
		constexpr inline auto metadata<tags::name<long long int>> =
			"long long int"_sv;
		template <>
		constexpr inline auto metadata<tags::name<unsigned short int>> =
			"unsigned short int"_sv;
		template <>
		constexpr inline auto metadata<tags::name<unsigned int>> =
			"unsigned int"_sv;
		template <>
		constexpr inline auto metadata<tags::name<unsigned long int>> =
			"unsigned long int"_sv;
		template <>
		constexpr inline auto metadata<tags::name<unsigned long long int>> =
			"unsigned long long int"_sv;
#ifdef __cpp_char8_t
		template <>
		constexpr inline auto metadata<tags::name<char8_t>> = "char8_t"_sv;
#endif
#ifdef __cpp_unicode_characters
		template <>
		constexpr inline auto metadata<tags::name<char16_t>> = "char16_t"_sv;
		template <>
		constexpr inline auto metadata<tags::name<char32_t>> = "char32_t"_sv;
#endif

		template <typename Class, typename... Parameters>
		constexpr inline auto
			metadata<tags::is_explicit<Class, Parameters...>> = PP::value_false;

		template <typename E>
		constexpr inline auto metadata<tags::enum_fixed_type<E>> =
			PP::type_void;
	}
}

#endif
