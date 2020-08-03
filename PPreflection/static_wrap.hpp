#pragma once
#include <cstddef>
#include <array>

template <typename T>
class static_wrap
{
	alignas(alignof(T))
		std::array<std::byte, sizeof(T)> data;

public:
	constexpr static_wrap(void (*f)(void*, const dynamic_ptr*), void** args)
		: data()
	{
		f(&get(), args);
	}

	constexpr T& get() noexcept
	{
		return *reinterpret_cast<T*>(data.data());
	}

	constexpr ~static_wrap()
	{
		get().~T();
	}
};

template <>
class static_wrap<void>
{
public:
	constexpr static_wrap(void (*f)(void*, const dynamic_ptr*), void** args)
	{
		f(nullptr, args);
	}
};
