#pragma once
#include "basic_overloaded_constructor.h"
#include "type.h"
#include "reflect.h"

template <typename Class, typename Constructors>
constexpr simple_range<const cref_t<member_like_function>> basic_overloaded_constructor<Class, Constructors>::get_overloads() const noexcept
{
	return reflect_many<Constructors, member_like_function>();
}
template <typename Class, typename Constructors>
constexpr const type& basic_overloaded_constructor<Class, Constructors>::get_enclosing_class() const noexcept
{
	return reflect<Class, type>();
}
