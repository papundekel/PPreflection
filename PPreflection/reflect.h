#pragma once
#include "pointer_view.h"
#include "view.hpp"
#include "value_t.hpp"
#include "type_t.hpp"
#include "overload_cast.h"
#include "tuple_map_to_array.hpp"

namespace reflection
{
	template <typename T> struct name {};
	template <typename T> struct id {};
	template <typename T> struct parent {};
	template <typename T> struct types {};
	template <typename T> struct namespaces {};
	template <typename T> struct functions {};
	template <typename T> struct base_classes {};
	template <typename T> struct nested_classes {};
	template <typename T> struct member_functions {};
	template <typename T> struct static_member_functions {};
	template <typename T> struct enum_values {};
	template <typename T> struct overloads {};
	template <typename T> struct overload {};
	template <typename T> struct constructors {};
	template <typename Class, typename... Parameters> struct constructor {};
	template <typename Class, typename... Parameters> struct is_explicit {};
	template <typename... Parameters> struct constructor_parameters {};
	template <typename Class, typename Return> struct conversion_function {};
}

template <typename T>
constexpr auto&& reflect_helper(PP::type_t<T>) noexcept;
template <auto v>
constexpr auto&& reflect_helper(PP::value_t<v>) noexcept
{
	return reflect_helper(PP::type_v<PP::value_t<v>>);
}

constexpr inline auto reflect = [](auto&& x) -> decltype(auto) { return reflect_helper(std::forward<decltype(x)>(x)); };

constexpr auto reflect_many(PP::tuple_like auto&& tuple, auto type) noexcept
{
	return PP::tuple_map_to_array(reflect, std::forward<decltype(tuple)>(tuple), type);
}

// namespace
//
// template <> constexpr inline auto reflection::metadata<type> = detail::basic_namespace<type>{};
// template <> constexpr inline auto reflection::metadata<reflection::name<type>> = std::string_view(name);
// template <> constexpr inline auto reflection::metadata<reflection::parent<type>> = PP::type_v<parent>;
// template <> constexpr inline auto reflection::metadata<reflection::types<type>> = PP::type_tuple_v<>;
// template <> constexpr inline auto reflection::metadata<reflection::namespaces<type>> = PP::type_tuple_v<>;

// struct
//
// template <> constexpr inline auto reflection::metadata<reflection::name<type>> = std::string_view("S");
// template <> constexpr inline auto reflection::metadata<reflection::parent<type>> = PP::type_v<parent>;
// template <> constexpr inline auto reflection::metadata<reflection::nested_classes<type>> = PP::type_tuple_v<>;
// template <> constexpr inline auto reflection::metadata<reflection::base_classes<type>> = PP::type_tuple_v<>;
