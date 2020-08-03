#pragma once
#include <cstddef>
#include <memory>
#include "reflect.hpp"

class type;

class dynamic_wrap
{
	struct deleter
	{
		const type& type;

		constexpr void operator()(std::byte* ptr) noexcept
		{
			type.destroy(ptr);
			delete[] ptr;
		}
	};

	std::unique_ptr<std::byte[], deleter> ptr;

public:
	constexpr dynamic_wrap(const type& t, void (*f)(void*, void**), void** args)
		: ptr(new std::byte[t.size()], { t })
	{
		f(ptr.get(), args);
	}

	template <typename T>
	constexpr std::unique_ptr<T> cast() noexcept
	{
		if (reflect<T> == ptr.get_deleter().type)
			return { ptr.release() };
		else
			return nullptr;
	}
};
