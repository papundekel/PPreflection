#pragma once
#include "basic_overloaded_member_function.h"
#include "function.h"
#include "type.h"
#include "get_value.h"

template <typename ID, typename Functions>
constexpr simple_range<const cref_t<member_function>> detail::basic_overloaded_member_function<ID, Functions>::get_overloads() const noexcept
{
	return reflect_many<Functions, member_function>();
}
template <typename ID, typename Functions>
constexpr const type& detail::basic_overloaded_member_function<ID, Functions>::get_enclosing_class() const noexcept
{
	return get_overloads().begin()->get().get_enclosing_class();
}
