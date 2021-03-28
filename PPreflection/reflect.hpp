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

#include "dynamic_object.hpp"
#include "dynamic_reference.hpp"
#include "get_type_class.hpp"

#include "descriptor.hpp"
#include "Namespace.hpp"

#include "basic_namespace.h"

#include "types/types.hpp"
#include "types/implementations/implementations.hpp"

#include "functions/functions.hpp"
#include "functions/implementations/implementations.hpp"

#include "types/dynamic_function_type.h"
#include "make_array.h"
#include "types/dynamic_enum_type.h"

#include "parent_descriptor_reference.hpp"
#include "parent_descriptor_reference_strong.hpp"
#include "convertor.hpp"
#include "types/array_type_reference.h"

#include "overload_cast.h"

namespace PPreflection
{
	namespace detail
	{
		struct overload_caster__no_specialization {};

		template <typename Overload, PP::size_t Index>
		constexpr inline overload_caster__no_specialization overload_caster = {};

		constexpr inline auto basic_types = PP::template_tuple<
			basic_reference_type,
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
		constexpr inline auto metadata = detail::basic_types[PP::value_t_static_cast(PP::type_size_t, get_type_class_value_t(PP::type<T>))](PP::type<T>)();

		template <> constexpr inline auto metadata<tags::global> = PPreflection::detail::basic_namespace<tags::global>{};

		constexpr auto&& reflect_helper(PP::concepts::type auto t) noexcept
		{
			return metadata<PP_GET_TYPE(PP::remove_cv(t))>;
		}
	}

	constexpr inline const Namespace& global_namespace = reflect(PP::type<tags::global>);
	constexpr inline const arithmetic_type_strong<float>& float_type = reflect(PP::type<float>);
}

using namespace PP::literals;

template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<PPreflection::tags::global>> = ""_sv;

template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<void					>> = "void"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<decltype(nullptr)		>> = "decltype(nullptr)"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<float					>> = "float"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<double				>> = "double"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<long double			>> = "long double"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<bool					>> = "bool"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<char					>> = "char"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<signed char			>> = "signed char"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<unsigned char			>> = "unsigned char"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<wchar_t				>> = "wchar_t"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<short int				>> = "short int"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<int					>> = "int"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<long int				>> = "long int"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<long long int			>> = "long long int"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<unsigned short int	>> = "unsigned short int"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<unsigned int			>> = "unsigned int"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<unsigned long int		>> = "unsigned long int"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<unsigned long long int>> = "unsigned long long int"_sv;
#ifdef __cpp_char8_t
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<char8_t				>> = "char8_t"_sv;
#endif
#ifdef __cpp_unicode_characters
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<char16_t				>> = "char16_t"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<char32_t				>> = "char32_t"_sv;
#endif

template <typename Class, typename... Parameters>
constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::is_explicit<Class, Parameters...>> = PP::value_false;

template <typename E>
constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::enum_fixed_type<E>> = PP::type_void;

#endif
