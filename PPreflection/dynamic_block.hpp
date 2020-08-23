#pragma once
#include <memory>
#include "dynamic_block.h"

template <typename T>
constexpr dynamic_block<T>::dynamic_block(std::size_t count) noexcept
	: count_(count)
	, buffer(new b[count_])
{}

template <typename T>
constexpr T* dynamic_block<T>::begin_helper() const noexcept
{
	return reinterpret_cast<T*>(buffer.get());
}
template <typename T>
constexpr T* dynamic_block<T>::end_helper() const noexcept
{
	return begin_helper() + count_;
}

template <typename T>
constexpr T* dynamic_block<T>::begin() noexcept
{
	return begin_helper();
}
template <typename T>
constexpr const T* dynamic_block<T>::begin() const noexcept
{
	return begin_helper();
}
template <typename T>
constexpr T* dynamic_block<T>::end() noexcept
{
	return end_helper();
}
template <typename T>
constexpr const T* dynamic_block<T>::end() const noexcept
{
	return end_helper();
}

template <typename T>
constexpr std::size_t dynamic_block<T>::count() const noexcept
{
	return count_;
}
