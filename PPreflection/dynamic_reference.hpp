#pragma once
#include <type_traits>
#include <utility>
#include <exception>
#include "dynamic_reference.h"
#include "type.h"
#include "reflect.h"

constexpr dynamic_reference::dynamic_reference(void* ptr, const type& t) noexcept
	: ptr(ptr)
	, t(t)
{}

constexpr const type& dynamic_reference::get_type() const noexcept
{
	return t;
}

template <PP::different_cvref<dynamic_reference> R>
constexpr dynamic_reference::dynamic_reference(R&& reference) noexcept
	: dynamic_reference(const_cast<std::remove_const_t<std::remove_reference_t<R>>*>(&reference), reflect<R&&, type>())
{}

template <typename T>
constexpr T&& dynamic_reference::cast_unsafe() const
{
	return std::forward<T>(*reinterpret_cast<std::remove_reference_t<T>*>(ptr));
}

template <typename T>
constexpr T&& dynamic_reference::cast() const
{
	if (t.make_reference<std::is_rvalue_reference_v<T>>().can_reference_initialize_no_user_conversion(reflect<T, type>()))
		return cast_unsafe<T>();
	else
		throw 0;
}

template <typename T>
T* dynamic_reference::get_ptr() const
{
	if (t.remove_reference().can_pointer_like_initialize_inner(reflect<T, type>()))
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
