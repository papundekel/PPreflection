#pragma once
#include <cstddef>
#include <utility>
#include <algorithm>
#include <memory>
#include "simple_vector.h"
#include "unique_ptr.h"

template <typename T>
constexpr unique_ptr<T[]> simple_vector<T>::allocate()
{
	return unique_ptr<T[]>(new T[capacity_]);
}

template <typename T>
constexpr T* simple_vector<T>::release_ptr() const noexcept
{
	return std::exchange(ptr, nullptr);
}

template <typename T>
constexpr simple_vector<T>::simple_vector() noexcept(noexcept(T()))
	: capacity_(16)
	, count_(0)
	, ptr(allocate())
{}

template <typename T>
template <typename U>
constexpr void simple_vector<T>::push_back(U&& value)
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

template <typename T>
constexpr void simple_vector<T>::clear() noexcept
{
	capacity_ = 16;
	count_ = 0;
	ptr = allocate();
}

template <typename T>
constexpr T* simple_vector<T>::begin() noexcept
{
	return ptr.get();
}

template <typename T>
constexpr T* simple_vector<T>::end() noexcept
{
	return ptr.get() + count_;
}

template <typename T>
constexpr const T* simple_vector<T>::begin() const noexcept
{
	return ptr.get();
}

template <typename T>
constexpr const T* simple_vector<T>::end() const noexcept
{
	return ptr.get() + count_;
}

template <typename T>
constexpr std::size_t simple_vector<T>::count() const noexcept
{
	return count_;
}
