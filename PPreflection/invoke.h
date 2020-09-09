#pragma once
#include <utility>

template <typename T, typename... Args>
constexpr decltype(auto) invoke(Args&&... args)
{
	return T::value_f(std::forward<Args>(args)...);
}
