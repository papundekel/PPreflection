#pragma once
#include <type_traits>
#include "reflect.h"
#include "transform_view.hpp"
#include "functional/id.hpp"
#include "is_user_defined_type.hpp"
#include "value_t.hpp"
#include "type_t.hpp"
#include "template_tuple.hpp"
#include "apply_template.hpp"
#include "tuple_map.hpp"
#include "get_type_class.hpp"
#include "fundamental_type_pack.h"
#include "functional/reorder.hpp"

#include "types/types.hpp"
#include "types/implementations/implementations.hpp"

#include "basic_namespace.h"

#include "functions/functions.h"
#include "functions/implementations/implementations.h"

#include "descriptor.hpp"

#include "functions/function.hpp"
#include "functions/member_function.hpp"

#include "types/dynamic_function_type.h"
#include "make_array.h"
#include "types/dynamic_enum_type.h"

namespace detail
{
	struct overload_caster__no_specialization {};

	template <typename Overload, std::size_t Index>
	constexpr inline overload_caster__no_specialization overload_caster = {};

	constexpr inline auto basic_types = PP::template_tuple_v<
		basic_reference_type,
		basic_void_type,
		basic_function_type,
		basic_unknown_bound_array_type,
		basic_known_bound_array_type,
		basic_non_void_fundamental_type,
		basic_pointer_type,
		basic_pointer_to_member_type,
		basic_non_union_class_type,
		basic_union_type,
		basic_enum_type>;
}

namespace reflection
{
	template <typename T>
	constexpr inline auto metadata =
		PP::get_type<decltype(PP::apply_template(get(PP::value<(std::size_t)get_type_class(PP::type<T>)>, detail::basic_types), PP::type<T>))>{};
}

template <typename T>
constexpr auto&& reflect_helper(PP::type_t<T>) noexcept
{
	return reflection::metadata<T>;
}

using namespace std::literals::string_view_literals;

template <> constexpr inline auto reflection::metadata<reflection::name<Namespace::global>> = ""sv;

template <> constexpr inline auto reflection::metadata<reflection::name<void					>> = "void"sv;
template <> constexpr inline auto reflection::metadata<reflection::name<decltype(nullptr)		>> = "decltype(nullptr)"sv;
template <> constexpr inline auto reflection::metadata<reflection::name<float					>> = "float"sv;
template <> constexpr inline auto reflection::metadata<reflection::name<double					>> = "double"sv;
template <> constexpr inline auto reflection::metadata<reflection::name<long double				>> = "long double"sv;
template <> constexpr inline auto reflection::metadata<reflection::name<bool					>> = "bool"sv;
template <> constexpr inline auto reflection::metadata<reflection::name<char					>> = "char"sv;
template <> constexpr inline auto reflection::metadata<reflection::name<signed char				>> = "signed char"sv;
template <> constexpr inline auto reflection::metadata<reflection::name<unsigned char			>> = "unsigned char"sv;
template <> constexpr inline auto reflection::metadata<reflection::name<wchar_t					>> = "wchar_t"sv;
template <> constexpr inline auto reflection::metadata<reflection::name<short int				>> = "short int"sv;
template <> constexpr inline auto reflection::metadata<reflection::name<int						>> = "int"sv;
template <> constexpr inline auto reflection::metadata<reflection::name<long int				>> = "long int"sv;
template <> constexpr inline auto reflection::metadata<reflection::name<long long int			>> = "long long int"sv;
template <> constexpr inline auto reflection::metadata<reflection::name<unsigned short int		>> = "unsigned short int"sv;
template <> constexpr inline auto reflection::metadata<reflection::name<unsigned int			>> = "unsigned int"sv;
template <> constexpr inline auto reflection::metadata<reflection::name<unsigned long int		>> = "unsigned long int"sv;
template <> constexpr inline auto reflection::metadata<reflection::name<unsigned long long int	>> = "unsigned long long int"sv;
#ifdef __cpp_char8_t
template <> constexpr inline auto reflection::metadata<reflection::name<char8_t					>> = "char8_t"sv;
#endif
#ifdef __cpp_unicode_characters
template <> constexpr inline auto reflection::metadata<reflection::name<char16_t				>> = "char16_t"sv;
template <> constexpr inline auto reflection::metadata<reflection::name<char32_t				>> = "char32_t"sv;
#endif

template <typename Class, typename... Parameters> constexpr inline auto reflection::metadata<reflection::is_explicit<Class, Parameters...>> = false;
template <typename Class, typename... Parameters> constexpr inline auto reflection::metadata<reflection::constructor<Class, Parameters...>>
	 = detail::basic_constructor<Class, Parameters...>{};
