#pragma once
#include "unique_raw_pointer.h"
#include <utility>

template <typename T>
constexpr unique_raw_pointer<T>::unique_raw_pointer(T* ptr) noexcept
	: ptr(ptr)
{}
template <typename T>
constexpr unique_raw_pointer<T>::unique_raw_pointer(unique_raw_pointer&& other) noexcept
	: ptr(std::exchange(other.ptr, nullptr))
{}
template <typename T>
constexpr unique_raw_pointer<T>& unique_raw_pointer<T>::operator=(unique_raw_pointer&& other) noexcept
{
	ptr = std::exchange(other.ptr, nullptr);
	return *this;
}
template <typename T>
constexpr T* unique_raw_pointer<T>::get() const noexcept
{
	return ptr;
}
