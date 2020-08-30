#pragma once
#include "basic_overloaded_static_member_function.h"
#include "function.h"
#include "type.h"
#include "reflect.h"

template <typename ID, typename Class, typename Functions>
constexpr simple_range<const cref_t<member_like_function>> basic_overloaded_static_member_function<ID, Class, Functions>::get_overloads() const noexcept
{
	return reflect_many<Functions, member_like_function>();
}
template <typename ID, typename Class, typename Functions>
constexpr const type& basic_overloaded_static_member_function<ID, Class, Functions>::get_enclosing_class() const noexcept
{
	return reflect<Class, type>();
}
