#pragma once
#include <type_traits>
#include <utility>
#include <exception>
#include "dynamic_reference.h"
#include "types/reference_type.h"
#include "reflect.h"
#include "../PP/PP/overloaded.hpp"

constexpr dynamic_reference::dynamic_reference(void* ptr, const reference_type& t) noexcept
	: ptr(ptr)
	, t(t)
{}

constexpr const reference_type& dynamic_reference::get_type() const noexcept
{
	return t;
}

template <typename T>
constexpr T&& dynamic_reference::cast_unsafe() const
{
	return std::forward<T>(*reinterpret_cast<std::remove_reference_t<T>*>(ptr));
}

template <typename T>
constexpr T&& dynamic_reference::cast() const
{
	if (type::reflect<T&&>().can_be_initialized_no_conversion(t.make_reference<std::is_rvalue_reference_v<T&&>>()))
		return cast_unsafe<T>();
	else
		throw bad_cast_exception{};
}

template <typename T>
T* dynamic_reference::get_ptr() const
{
	if (type::reflect<T>().can_be_pointer_initialized(t.remove_reference()))
		return reinterpret_cast<T*>(ptr);
	else
		return nullptr;
}

template <typename T>
T& dynamic_reference::get_ref() const&
{
	return cast<T&>();
}

template <typename T>
T&& dynamic_reference::get_ref() const&&
{
	return cast<T&&>();
}

dynamic_reference dynamic_reference::move() const
{
	return { ptr, t.make_reference<true>() };
}

template <PP::different_cvref<dynamic_reference> R>
constexpr dynamic_reference::dynamic_reference(R&& reference) noexcept
	: dynamic_reference(const_cast<std::remove_const_t<std::remove_reference_t<R>>*>(&reference), type::reflect<R&&>())
{}
