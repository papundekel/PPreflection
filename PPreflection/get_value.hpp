#pragma once
#include "get_value.h"

template <typename T>
constexpr detail::get_value__no_value_member get_value() noexcept
{
	return {};
}
template <typename T>
requires (detail::has_value_f<T>)
constexpr decltype(auto) get_value() noexcept
{
	return T::value_f();
}
template <typename T>
requires (!detail::has_value_f<T> && detail::has_value<T>)
constexpr decltype(auto) get_value() noexcept
{
	return (T::value);
}
