#pragma once
#include <memory>
#include <utility>
#include "array_vector.h"

template <typename T, std::size_t capacity_>
constexpr T* array_vector<T, capacity_>::begin_helper() noexcept
{
	return reinterpret_cast<T*>(&buffer);
}
template <typename T, std::size_t capacity_>
constexpr T* array_vector<T, capacity_>::end_helper() noexcept
{
	return begin_helper() + count_;
}

template <typename T, std::size_t capacity_>
constexpr array_vector<T, capacity_>::array_vector() noexcept
{}
template <typename T, std::size_t capacity_>
constexpr array_vector<T, capacity_>::array_vector(const array_vector& other) noexcept(std::is_nothrow_copy_constructible_v<T>)
{
	std::uninitialized_copy(other.begin(), other.end(), begin());
}
template <typename T, std::size_t capacity_>
constexpr array_vector<T, capacity_>::array_vector(array_vector&& other) noexcept(std::is_nothrow_move_constructible_v<T>)
{
	std::uninitialized_move(other.begin(), other.end(), begin());
}

template <typename T, std::size_t capacity_>
constexpr void array_vector<T, capacity_>::destroy_all() noexcept
{
	std::destroy(begin(), end());
}

template <typename T, std::size_t capacity_>
constexpr array_vector<T, capacity_>::~array_vector()
{
	destroy_all();
}

template <typename T, std::size_t capacity_>
constexpr T* array_vector<T, capacity_>::begin() noexcept
{
	return begin_helper();
}
template <typename T, std::size_t capacity_>
constexpr const T* array_vector<T, capacity_>::begin() const noexcept
{
	return begin_helper();
}
template <typename T, std::size_t capacity_>
constexpr T* array_vector<T, capacity_>::end() noexcept
{
	return end_helper();
}
template <typename T, std::size_t capacity_>
constexpr const T* array_vector<T, capacity_>::end() const noexcept
{
	return end_helper();
}

template <typename T, std::size_t capacity_>
constexpr bool array_vector<T, capacity_>::empty() const noexcept
{
	return count_ == 0;
}

template <typename T, std::size_t capacity_>
constexpr void array_vector<T, capacity_>::clear() noexcept
{
	destroy_all();
	count_ = 0;
}

template <typename T, std::size_t capacity_>
template <typename U>
constexpr void array_vector<T, capacity_>::push_back(U&& object) noexcept(std::is_nothrow_constructible_v<T, U>)
{
	if (count_ < capacity_)
	{
		std::construct_at(end_helper(), std::forward<U>(object));
		++count_;
	}
	else
		std::terminate();
}

template <typename T, std::size_t capacity_>
constexpr void array_vector<T, capacity_>::pop_back() noexcept
{
	if (count_ != 0)
	{
		--count_;
		std::destroy_at(end_helper());
	}
	else
		std::terminate();
}
