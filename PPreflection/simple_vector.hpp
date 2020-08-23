#pragma once
#include <cstddef>
#include <utility>
#include <algorithm>
#include <memory>
#include "simple_vector.h"

template <typename T>
constexpr simple_vector<T>::simple_vector(std::size_t capacity) noexcept
	: count_(0)
	, block(capacity)
{}
template <typename T>
constexpr simple_vector<T>::simple_vector() noexcept
	: simple_vector(default_capacity)
{}
template <typename T>
constexpr void simple_vector<T>::destroy_all() noexcept
{
	std::destroy(begin(), end());
}

template <typename T>
constexpr simple_vector<T>::~simple_vector()
{
	destroy_all();
}

template <typename T>
template <typename U>
constexpr void simple_vector<T>::push_back(U&& value)
{
	if (count() == capacity())
	{
		dynamic_block<T> new_block(2 * capacity());

		std::uninitialized_move(begin(), end(), new_block.begin());

		destroy_all();

		block = std::move(new_block);
	}

	std::construct_at(end(), std::forward<U>(value));

	++count_;
}

template <typename T>
constexpr void simple_vector<T>::clear() noexcept
{
	std::destroy_at(this);
	std::construct_at(this);
}

template <typename T>
constexpr T* simple_vector<T>::begin() noexcept
{
	return block.begin();
}

template <typename T>
constexpr T* simple_vector<T>::end() noexcept
{
	return begin() + count_;
}

template <typename T>
constexpr const T* simple_vector<T>::begin() const noexcept
{
	return block.begin();
}

template <typename T>
constexpr const T* simple_vector<T>::end() const noexcept
{
	return begin() + count_;
}

template <typename T>
constexpr std::size_t simple_vector<T>::count() const noexcept
{
	return count_;
}

template <typename T>
constexpr std::size_t simple_vector<T>::capacity() const noexcept
{
	return block.count();
}
