#pragma once
#include <type_traits>
#include <vector>
#include "function.h"
#include "../dynamic_object.h"
#include "../types/type.h"
#include "../types/parameter_type_reference.h"
#include "../dynamic_reference.h"

constexpr void function::print_name_basic(PP::simple_ostream& out) const noexcept
{
	get_overloaded_function().print_name(out);
	type::print_parameter_types(out, parameter_types());
}

constexpr void function::print_noexcept(PP::simple_ostream& out) const noexcept
{
	if (is_noexcept())
		out.write(" noexcept");
}
constexpr void function::print_name_before_parent(PP::simple_ostream& out) const noexcept
{
	const descriptor& rtd = return_type();
	rtd.print_name(out);
}
constexpr void function::print_name_after_parent(PP::simple_ostream& out) const noexcept
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
constexpr decltype(auto) function::invoke_helper_t<Parameters...>::x::helper(F&& f, PP::any_iterator<const dynamic_reference&> arg_iterator, std::index_sequence<I...>) noexcept
{
	return std::forward<F>(f)(arg_iterator[I].cast_unsafe<Parameters>()...);
}

template <typename... Parameters>
template <typename F>
constexpr decltype(auto) function::invoke_helper_t<Parameters...>::x::value_f(F&& f, PP::any_iterator<const dynamic_reference&> arg_iterator) noexcept
{
	return helper(std::forward<F>(f), arg_iterator, std::index_sequence_for<Parameters...>{});
}

constexpr bool function::can_invoke(PP::any_view<const reference_type&> argument_types) const noexcept
{
	return parameter_type_reference::can_initialize_many(parameter_types(), argument_types);
}

inline dynamic_variable function::invoke(pointer_view<const dynamic_reference> args) const
{
	if (can_invoke(args | PP::transform([](const dynamic_reference& r) -> const reference_type& { return r.get_type(); })))
		return invoke_unsafe(PP::begin(args));
	else
		return dynamic_variable::create_invalid();
}

inline dynamic_variable overloaded_function::invoke(pointer_view<const dynamic_reference> args) const
{
	for (const function& f : get_overloads())
		if (f.can_invoke(args | PP::transform([](const dynamic_reference& r) -> const reference_type& { return r.get_type(); })))
			return f.invoke_unsafe(PP::begin(args));

	return dynamic_variable::create_invalid();
}
