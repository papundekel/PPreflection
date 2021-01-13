#pragma once
#include <utility>

template <typename T>
constexpr decltype(auto) invoke(auto&&... args)
{
	return T::value_f(PP_FORWARD(args)...);
}
