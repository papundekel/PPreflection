#pragma once
#include <type_traits>
#include <utility>
#include "basic_typed_function.h"

template <typename Overload, typename F, typename Base>
template <typename T>
constexpr void detail::basic_typed_function<Overload, F, Base>::invoke_(void* result, T&& t) noexcept
{
	using R = B::ReturnType;

	if constexpr (!std::is_void_v<R>)
	{
		if constexpr (!std::is_reference_v<R>)
			new (result) R(std::forward<T>(t)());
		else
		{
			auto&& x = std::forward<T>(t)();
			new (result) std::remove_reference_t<R>* (&x);
		}
	}
	else
		std::forward<T>(t)();
}
