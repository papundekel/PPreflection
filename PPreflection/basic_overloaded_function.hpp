#pragma once
#include "basic_overloaded_function.h"
#include "descriptor.h"

template <typename ID, typename Base>
constexpr void basic_overloaded_function<ID, Base>::print_name(simple_ostream& out) const noexcept
{
	out.write(descriptor::reflect_name<ID>());
}
template <typename ID, typename Base>
constexpr bool basic_overloaded_function<ID, Base>::has_name(std::string_view name) const noexcept
{
	return descriptor::reflect_name<ID>() == name;
}
