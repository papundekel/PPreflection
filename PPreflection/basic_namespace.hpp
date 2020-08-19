#pragma once
#include "basic_namespace.h"
#include "type.hpp"
#include "descriptor.h"

template <typename ID, typename Types, typename Functions>
constexpr simple_range<const cref_t<type>> detail::basic_namespace<ID, Types, Functions>::get_types() const noexcept
{
	return reflect_many<Types, type>();
}
template <typename ID, typename Types, typename Functions>
constexpr simple_range<const cref_t<namespace_function>> detail::basic_namespace<ID, Types, Functions>::get_functions() const noexcept
{
	return reflect_many<Functions, namespace_function>();
}

template <typename ID, typename Types, typename Functions>
constexpr void detail::basic_namespace<ID, Types, Functions>::print_name(simple_ostream& out) const noexcept
{
	out.write(descriptor::reflect_name<ID>());
}

template <typename ID, typename Types, typename Functions>
constexpr bool detail::basic_namespace<ID, Types, Functions>::has_name(std::string_view name) const noexcept
{
	return descriptor::reflect_name<ID>() == name;
}
