#pragma once
#include "cref_t.h"

template <typename T>
constexpr cref_t<T>::cref_t(const T& ref) noexcept
	: ptr(&ref)
{}

template <typename T>
constexpr const T& cref_t<T>::get() const noexcept
{
	return *ptr;
}

template <typename T>
constexpr cref_t<T>::operator const T&() const noexcept
{
	return get();
}
