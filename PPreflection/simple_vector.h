#pragma once
#include <cstddef>
#include <utility>
#include <algorithm>
#include <memory>
#include "dynamic_block.h"

template <typename T>
class simple_vector
{
	static constexpr std::size_t default_capacity = 16;

	std::size_t count_;
	dynamic_block<T> block;

	constexpr void destroy_all() noexcept;

public:
	explicit constexpr simple_vector(std::size_t capacity) noexcept;
	constexpr simple_vector() noexcept;

	constexpr ~simple_vector();

	template <typename U>
	constexpr void push_back(U&& value);

	constexpr void clear() noexcept;

	constexpr T* begin() noexcept;
	constexpr T* end() noexcept;
	constexpr const T* begin() const noexcept;
	constexpr const T* end() const noexcept;

	constexpr std::size_t count() const noexcept;
	constexpr std::size_t capacity() const noexcept;
};
