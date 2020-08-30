#pragma once
#include "namespace_t.h"
#include "basic_namespace_function.h"
#include "basic_static_function.h"
#include "overloaded_namespace_function.h"

template <typename Overload, auto f>
constexpr const overloaded_namespace_function& detail::basic_namespace_function<Overload, f>::get_overloaded_function() const noexcept
{
	return reflect<Overload, overloaded_namespace_function>();
}
