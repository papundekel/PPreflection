#pragma once
#include <type_traits>
#include "simple_range.h"

template <typename T>
constexpr simple_range<T>::simple_range(T* begin, T* end) noexcept
	: begin_(begin)
	, end_(end)
{}

template <typename T>
constexpr simple_range<T>::simple_range() noexcept
	: simple_range(nullptr, nullptr)
{}

template <typename T>
template <std::size_t c>
constexpr simple_range<T>::simple_range(const std::array<std::remove_const_t<T>, c> & array) noexcept
	: simple_range(array.data(), array.data() + array.size())
{}

template <typename T>
constexpr simple_range<T>::simple_range(const std::initializer_list<std::remove_const_t<T>>& list) noexcept
	: simple_range(list.begin(), list.end())
{}

template <typename T>
constexpr auto simple_range<T>::begin() const noexcept
{
	return begin_;
}

template <typename T>
constexpr auto simple_range<T>::end() const noexcept
{
	return end_;
}

template <typename T>
constexpr auto simple_range<T>::count() const noexcept
{
	return end() - begin();
}

template <typename T>
constexpr bool simple_range<T>::empty() const noexcept
{
	return begin() != end();
}

template <typename T>
constexpr auto& simple_range<T>::operator[](std::size_t index) const noexcept
{
	return begin()[index];
}
