#pragma once
#include <type_traits>
#include "function.h"
#include "dynamic_wrap.h"
#include "type.h"
#include "get_value.h"

template <typename... Parameters>
constexpr typename function::invoke_helper_t<Parameters...>::x function::invoke_helper_t<Parameters...>::value_f() noexcept
{
	return {};
}
template <typename... Parameters>
template <typename F, std::size_t... I>
constexpr decltype(auto) function::invoke_helper_t<Parameters...>::x::helper(F&& f, const dynamic_ptr* args, std::index_sequence<I...>) noexcept
{
	return std::forward<F>(f)(args[I].cast<Parameters>()...);
}

template <typename... Parameters>
template <typename F>
constexpr decltype(auto) function::invoke_helper_t<Parameters...>::x::operator()(F&& f, const dynamic_ptr* args) const noexcept
{
	return helper(std::forward<F>(f), args, std::index_sequence_for<Parameters...>{});
}

constexpr bool function::can_invoke(simple_range<const dynamic_ptr> args) const noexcept
{
	auto ps = parameter_types();

	if (ps.count() != args.count())
		return false;

	auto a = args.begin();
	for (auto p = ps.begin(); p != ps.end(); ++p, ++a)
		if (!a->get_type().can_initialize(p->get()))
			return false;
	
	return true;
}

constexpr dynamic_wrap function::invoke_unsafe(simple_range<const dynamic_ptr> args) const noexcept
{
	return dynamic_wrap(return_type(), [this, args](void* ptr) { invoke_implementation(ptr, args.begin()); });
}

constexpr dynamic_wrap function::invoke(simple_range<const dynamic_ptr> args) const
{
	if (can_invoke(args))
		return invoke_unsafe(args);
	else
		throw 0;
}
