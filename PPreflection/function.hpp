#pragma once
#include <type_traits>
#include <vector>
#include "function.h"
#include "dynamic_object.h"
#include "types/type.h"
#include "get_value.h"
#include "conversion_function.h"
#include "dynamic_reference.h"

constexpr void function::print_name_basic(simple_ostream& out) const noexcept
{
	get_overloaded_function().print_name(out);
	type::print_parameter_types(out, parameter_types());
}

constexpr void function::print_noexcept(simple_ostream& out) const noexcept
{
	if (is_noexcept())
		out.write(" noexcept");
}
constexpr void function::print_name_before_parent(simple_ostream& out) const noexcept
{
	return_type().print_name(out);
}
constexpr void function::print_name_after_parent(simple_ostream& out) const noexcept
{
	print_name_basic(out);
	print_noexcept(out);
}
constexpr bool function::has_name(std::string_view name) const noexcept
{
	return get_overloaded_function().has_name(name);
}

template <typename... Parameters>
template <typename F, std::size_t... I>
constexpr decltype(auto) function::invoke_helper_t<Parameters...>::x::helper(F&& f, any_iterator<const dynamic_reference&> arg_iterator, std::index_sequence<I...>) noexcept
{
	return std::forward<F>(f)(arg_iterator[I].cast_unsafe<Parameters>()...);
}

template <typename... Parameters>
template <typename F>
constexpr decltype(auto) function::invoke_helper_t<Parameters...>::x::value_f(F&& f, any_iterator<const dynamic_reference&> arg_iterator) noexcept
{
	return helper(std::forward<F>(f), arg_iterator, std::index_sequence_for<Parameters...>{});
}

constexpr bool function::can_invoke(any_view<const type&> argument_types) const noexcept
{
	return type::can_initialize_arguments(parameter_types(), argument_types);
}

constexpr dynamic_object function::invoke(pointer_view<const dynamic_reference> args) const
{
	if (can_invoke(args | PP::transform([](const dynamic_reference& r) -> const type& { return r.get_type(); })))
		return invoke_unsafe(PP::begin(args));
	else
		return dynamic_object::create_invalid();
}
