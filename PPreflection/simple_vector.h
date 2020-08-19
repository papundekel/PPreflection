#pragma once
#include <cstddef>
#include <utility>
#include <algorithm>
#include <memory>
#include "unique_ptr.h"

template <typename T>
class simple_vector
{
	std::size_t capacity_;
	std::size_t count_;
	unique_ptr<T[]> ptr;

	constexpr unique_ptr<T[]> allocate();

	constexpr T* release_ptr() const noexcept;

public:
	constexpr simple_vector() noexcept(noexcept(T()));

	template <typename U>
	constexpr void push_back(U&& value);

	constexpr void clear() noexcept;

	constexpr T* begin() noexcept;
	constexpr T* end() noexcept;
	constexpr const T* begin() const noexcept;
	constexpr const T* end() const noexcept;

	constexpr std::size_t count() const noexcept;
};
