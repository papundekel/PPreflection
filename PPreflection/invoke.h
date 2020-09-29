#pragma once
#include <utility>

template <typename T>
constexpr decltype(auto) invoke(auto&&... args)
{
	return T::value_f(std::forward<decltype(args)>(args)...);
}
