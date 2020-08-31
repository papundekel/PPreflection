#pragma once
#include <type_traits>
#include "reflect.h"
#include "value_t.h"
#include "map_pack.h"
#include "get_value.h"
#include "cref_t.h"

template <typename ResultType>
template <typename T>
constexpr const ResultType& detail::reflector<ResultType>::reflect<T>::value_f() noexcept
{
	if constexpr (!std::is_const_v<T> && !std::is_volatile_v<T> && (std::is_class_v<T> || std::is_enum_v<T>))
		return detail::reflect_owning<T>;
	else
		return detail::reflect_owning<detail::basic_type_wrap<T>>;
}

template <typename ResultType>
template <typename T>
constexpr const ResultType& detail::reflector<ResultType>::reflect<detail::id_wrap<T>>::value_f() noexcept
{
	return detail::reflect_owning<detail::id_wrap<T>>;
}
template <typename ResultType>
template <typename T>
constexpr const ResultType& detail::reflector<ResultType>::reflect<detail::name_wrap<T>>::value_f() noexcept
{
	return detail::reflect_owning<detail::name_wrap<T>>;
}
template <typename ResultType>
template <typename T>
constexpr const ResultType& detail::reflector<ResultType>::reflect<detail::constructor_wrap<T>>::value_f() noexcept
{
	return detail::reflect_owning<detail::constructor_wrap<T>>;
}

template <typename T, typename ResultType>
constexpr const ResultType& reflect() noexcept
{
	return get_value<typename detail::reflector<ResultType>::template reflect<T>>();
}

template <auto v, typename ResultType>
constexpr decltype(auto) reflect() noexcept
{
	return reflect<value_t<v>, ResultType>();
}

template <typename Pack, typename ResultType>
constexpr decltype(auto) reflect_many() noexcept
{
	return get_value<map_pack<detail::reflector<ResultType>::template reflect, Pack, cref_t<ResultType>>>();
}
