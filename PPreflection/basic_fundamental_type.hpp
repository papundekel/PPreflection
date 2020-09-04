#pragma once
#include "basic_fundamental_type.h"
#include "reflect.h"
#include "namespace_t.h"

template <typename T>
constexpr const namespace_t* detail::basic_fundamental_type<T>::get_namespace() const noexcept
{
	return &reflect<namespace_t::global, namespace_t>();
}
template <typename T>
constexpr const overloaded_constructor* detail::basic_fundamental_type<T>::get_constructors() const noexcept
{
	return &reflect<detail::constructor_wrap<T>, overloaded_constructor>();
}
