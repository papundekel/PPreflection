#pragma once
#include <type_traits>
#include <utility>
#include <exception>
#include "dynamic_ptr.h"
#include "type.h"
#include "reflect.h"

constexpr dynamic_ptr::dynamic_ptr(void* ptr, const type& t) noexcept
	: ptr(ptr)
	, t(t)
{}

constexpr const type& dynamic_ptr::get_type() const noexcept
{
	return t;
}

constexpr bool dynamic_ptr::lvalue() const noexcept
{
	return t.get_ref_qualifier() == ref_qualifier::lvalue;
}

template <typename T>
//requires (!std::is_same_v<std::remove_cvref_t<T>, dynamic_ptr>)
constexpr dynamic_ptr::dynamic_ptr(T&& rvalue) noexcept
	: ptr(const_cast<std::remove_const_t<std::remove_reference_t<T>>*>(&rvalue))
	, t(reflect<T&&, type>())
{}

template <typename T>
decltype(auto) dynamic_ptr::cast() const
{
	if constexpr (std::is_reference_v<T>)
		return std::forward<T>(*reinterpret_cast<std::remove_reference_t<T>*>(ptr));
	else
	{
		if (lvalue())
			return T(*reinterpret_cast<T*>(ptr));
		else
			return T(std::move(*reinterpret_cast<T*>(ptr)));
	}
}
