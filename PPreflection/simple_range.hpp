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
template <typename Container>
constexpr simple_range<T>::simple_range(const Container& container) noexcept
	: simple_range(std::begin(container), std::end(container))
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
