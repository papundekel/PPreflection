#pragma once
#include <array>
#include <initializer_list>
#include "cref_t.h"

template <typename T>
class simple_range
{
	T* begin_;
	T* end_;

public:
	constexpr simple_range(T* begin, T* end) noexcept;

	constexpr simple_range() noexcept;

	template <typename Container>
	constexpr simple_range(const Container& container) noexcept;

	constexpr simple_range(const std::initializer_list<std::remove_const_t<T>>& list) noexcept;

	constexpr auto begin() const noexcept;
	constexpr auto end() const noexcept;
	constexpr auto count() const noexcept;
	constexpr bool empty() const noexcept;
	constexpr auto& operator[](std::size_t index) const noexcept;
};

template <typename T>
simple_range(const std::initializer_list<T>&) -> simple_range<const T>;
