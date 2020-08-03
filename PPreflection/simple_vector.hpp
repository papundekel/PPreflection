#pragma once
#include <cstddef>
#include <utility>
#include <algorithm>
#include <memory>
#include "unique_ptr.hpp"

template <typename T>
class simple_vector
{
	std::size_t capacity_;
	std::size_t count_;
	unique_ptr<T[]> ptr;

	constexpr auto allocate()
	{
		return unique_ptr<T[]>(new T[capacity_]);
	}

	constexpr auto release_ptr() const noexcept
	{
		return std::exchange(ptr, nullptr);
	}

public:
	constexpr simple_vector() noexcept(noexcept(T()))
		: capacity_(16)
		, count_(0)
		, ptr(allocate())
	{}

	template <typename U>
	constexpr void push_back(U&& value) //noexcept(noexcept(std::declval<T>() = std::forward<U>(value)))
	{
		if (count_ == capacity_)
		{
			capacity_ *= 2;
			auto new_buffer = allocate();

			std::move(begin(), end(), new_buffer.get());

			ptr = std::move(new_buffer);
		}

		ptr[count_] = std::forward<U>(value);
		++count_;
	}

	constexpr void clear() noexcept
	{
		capacity_ = 16;
		count_ = 0;
		ptr = allocate();
	}

	constexpr T* begin() noexcept
	{
		return ptr.get();
	}
	constexpr T* end() noexcept
	{
		return ptr.get() + count_;
	}
	constexpr const T* begin() const noexcept
	{
		return ptr.get();
	}
	constexpr const T* end() const noexcept
	{
		return ptr.get() + count_;
	}

	constexpr auto count() const noexcept
	{
		return count_;
	}
};
