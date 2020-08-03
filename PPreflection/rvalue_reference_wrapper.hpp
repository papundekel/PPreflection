#pragma once
#include <type_traits>

template <typename T>
struct rvalue_reference_wrapper
{
	T* ptr;

	constexpr rvalue_reference_wrapper(T&& x) noexcept
		: ptr(&x)
	{}

	constexpr T&& get() && noexcept
	{
		return std::move(*std::exchange(ptr, nullptr));
	}

	constexpr operator T && () && noexcept
	{
		return get();
	}
};

template <typename T>
requires (!std::is_reference_v<T>)
constexpr auto rref(T&& x) noexcept
{
	return rvalue_reference_wrapper<T>(std::move(x));
}
