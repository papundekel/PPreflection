#pragma once
#include "basic_overloaded_namespace_function.h"
#include "function.h"
#include "namespace_t.h"

template <typename ID, typename Namespace, typename Functions>
constexpr simple_range<const cref_t<namespace_function>> detail::basic_overloaded_namespace_function<ID, Namespace, Functions>::get_overloads() const noexcept
{
	return reflect_many<Functions, namespace_function>();
}

template <typename ID, typename Namespace, typename Functions>
constexpr const namespace_t& detail::basic_overloaded_namespace_function<ID, Namespace, Functions>::get_enclosing_namespace() const noexcept
{
	return reflect<Namespace, namespace_t>();
}
