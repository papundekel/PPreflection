#pragma once
#include "overload_cast.h"
#include "tuple_map_to_array.hpp"
#include "type_t.hpp"
#include "value_t.hpp"
#include "view.hpp"

namespace PPreflection
{
	namespace tags
	{
		template <typename T> struct name;
		template <typename T> struct id;
		template <typename T> struct parent;
		template <typename T> struct types;
		template <typename T> struct namespaces;
		template <typename T> struct functions;
		template <typename T> struct base_classes;
		template <typename T> struct nested_classes;
		template <typename T> struct member_functions;
		template <typename T> struct static_member_functions;
		template <typename T> struct enum_values;
		template <typename T> struct overloads;
		template <typename T> struct overload;
		template <typename T> struct constructors;
		template <typename Class, typename... Parameters> struct constructor;
		template <typename Class, typename... Parameters> struct is_explicit;
		template <typename... Parameters> struct constructor_parameters;
		template <typename Class, typename Return> struct conversion_function;
	}

	namespace detail
	{
		constexpr auto&& reflect_helper(PP::concepts::type auto t) noexcept;
		constexpr auto&& reflect_helper(PP::concepts::value auto v) noexcept
		{
			return reflect_helper(PP_DECLTYPE(PP::to_value_t(v)));
		}
	}

	PP_FUNCTOR(reflect, auto x) -> decltype(auto)
	{
		return detail::reflect_helper(x);
	});

	constexpr auto reflect_many(PP::concepts::type auto t, PP::concepts::tuple auto&& tuple) noexcept
	{
		return PP::tuple_map_to_array(t, reflect, PP_FORWARD(tuple));
	}

	PP_FUNCTOR(reflect_many_helper, PP::concepts::type auto tag_type, auto Template, PP::concepts::type auto t) noexcept
	{
		return reflect_many(t, reflect(Template(tag_type)));
	});
}

// namespace
//
// template <> constexpr inline auto PPreflection::detail::metadata<namespace> = PPreflection::detail::basic_namespace<type>{};
// template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<namespace>> = "name"_sv;
// template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::parent<namespace>> = PP::type<parent>;
// template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::types<namespace>> = PP::type_tuple<types...>;
// template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::namespaces<namespace>> = PP::type_tuple<namespaces...>;

// class
//
// template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<type>> = "type"_sv;
// template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::parent<type>> = PP::type<parent>;
// template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::nested_classes<type>> = PP::type_tuple<nested_classes...>;
// template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::base_classes<type>> = PP::type_tuple<bases...>;
