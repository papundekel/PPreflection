#pragma once
#include "PP/constant_string.hpp"
#include "PP/tuple_map_to_array.hpp"
#include "PP/type_t.hpp"
#include "PP/value_t.hpp"
#include "PP/view.hpp"

namespace PPreflection::tags
{
namespace
{
template <typename T>
struct descriptor;
template <typename T>
struct name;
template <typename T>
struct id;
template <typename T>
struct parent;
template <typename T>
struct types;
template <typename T>
struct namespaces;
template <typename T>
struct functions;
template <typename T>
struct base_classes;
template <typename T>
struct nested_types;
template <typename T>
struct member_functions;
template <typename T>
struct non_conversion_member_functions;
template <typename T>
struct conversion_functions;
template <typename T>
struct static_member_functions;
template <typename T>
struct enum_values;
template <typename T>
struct enum_fixed_type;
template <typename T>
struct overloads;
template <typename T>
struct overload;
template <typename T>
struct constructors;
template <typename Class, typename... Parameters>
struct constructor;
template <typename Class, typename... Parameters>
struct is_explicit;
template <typename... Parameters>
struct constructor_parameters;
template <typename Class, typename Return>
struct conversion_function;

struct global;
}
}

namespace PPreflection::detail
{
constexpr auto& reflect_helper(PP::concepts::type auto t) noexcept;

constexpr auto& reflect_helper(PP::concepts::value auto v) noexcept
{
	return reflect_helper(PP_DECLTYPE(PP::to_value_t(v)));
}

constexpr auto& reflect_descriptor_helper(PP::concepts::type auto t) noexcept
{
	return reflect_helper(PP::Template<tags::descriptor>(PP::remove_cv(t)));
}

constexpr auto& reflect_descriptor_helper(PP::concepts::value auto v) noexcept
{
	return reflect_descriptor_helper(PP_DECLTYPE(PP::to_value_t(v)));
}
}

namespace PPreflection
{
constexpr auto reflect = PP::functor(
	[](auto x) -> decltype(auto)
	{
		return detail::reflect_helper(x);
	});
constexpr auto reflect_descriptor = PP::functor(
	[](auto x) -> decltype(auto)
	{
		return detail::reflect_descriptor_helper(x);
	});
}

namespace PPreflection::detail
{
constexpr auto reflect_many(PP::concepts::type auto t,
                            PP::concepts::tuple auto&& tuple) noexcept
{
	return PP::tuple_map_to_array(t, reflect_descriptor, PP_F(tuple));
}

constexpr auto reflect_many_helper = PP::functor(
	[](PP::concepts::type auto tag_type,
       auto Template,
       PP::concepts::type auto t) noexcept
	{
		return reflect_many(t, reflect(Template(tag_type)));
	});
}
