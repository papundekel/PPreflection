#pragma once
#include <type_traits>
#include <utility>
#include <exception>
#include "dynamic_reference.h"
#include "types/reference_type.h"
#include "reflect.h"
#include "overloaded.hpp"
#include "types/type.h"

constexpr dynamic_reference::dynamic_reference(const void* ptr, const reference_type& t) noexcept
	: ptr(const_cast<void*>(ptr))
	, t(t)
{}

constexpr const reference_type& dynamic_reference::get_type() const noexcept
{
	return t;
}

template <typename T>
constexpr T&& dynamic_reference::cast_unsafe(PP::type_t<T>) const noexcept
{
	return std::forward<T>(*reinterpret_cast<std::remove_reference_t<T>*>(ptr));
}

template <typename T>
constexpr T&& dynamic_reference::cast(PP::type_t<T>) const
{
	if (type::reflect(PP::type<T&&>).can_be_initialized(t.make_reference<std::is_rvalue_reference_v<T&&>>()))
		return cast_unsafe<T>();
	else
		throw bad_cast_exception{};
}

template <typename T>
T* dynamic_reference::get_ptr() const
{
	if (type::reflect(PP::type<T>).can_be_pointer_initialized(t.remove_reference()))
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

template <typename R>
requires PP::different_cvref<dynamic_reference, R>
	&& PP::different_cvref<dynamic_object, R>
	&& PP::different_cvref<dynamic_variable, R>
constexpr dynamic_reference::dynamic_reference(R&& reference) noexcept
	: dynamic_reference(&reference, type::reflect(PP::type<R&&>))
{}
