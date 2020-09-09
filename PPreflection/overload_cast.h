#pragma once
#include "../PP/PP/cv_qualifier.hpp"
#include "../PP/PP/ref_qualifier.hpp"
#include "../PP/PP/add_function_cvrefn.hpp"

namespace detail
{
	template <typename... Args>
	struct overload_caster_helper
	{
		template <typename Return>
		constexpr auto operator()(Return(*x)(Args...)) const noexcept { return x; }
		template <typename Return>
		constexpr auto operator()(Return(*x)(Args...) noexcept) const noexcept { return x; }
	};

	template <PP::cv_qualifier cv, PP::ref_qualifier ref, typename... Args>
	struct overload_member_caster_helper
	{
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...)) const noexcept { return x; }
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) noexcept) const noexcept { return x; }
	};
	template <typename... Args>
	struct overload_member_caster_helper<PP::cv_qualifier::const_, PP::ref_qualifier::none, Args...>
	{
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) const) const noexcept { return x; }
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) const noexcept) const noexcept { return x; }
	};
	template <typename... Args>
	struct overload_member_caster_helper<PP::cv_qualifier::volatile_, PP::ref_qualifier::none, Args...>
	{
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) volatile) const noexcept { return x; }
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) volatile noexcept) const noexcept { return x; }
	};
	template <typename... Args>
	struct overload_member_caster_helper<PP::cv_qualifier::const_volatile, PP::ref_qualifier::none, Args...>
	{
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) const volatile) const noexcept { return x; }
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) const volatile noexcept) const noexcept { return x; }
	};
	template <typename... Args>
	struct overload_member_caster_helper<PP::cv_qualifier::none, PP::ref_qualifier::lvalue, Args...>
	{
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) &) const noexcept { return x; }
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) & noexcept) const noexcept { return x; }
	};
	template <typename... Args>
	struct overload_member_caster_helper<PP::cv_qualifier::const_, PP::ref_qualifier::lvalue, Args...>
	{
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) const&) const noexcept { return x; }
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) const& noexcept) const noexcept { return x; }
	};
	template <typename... Args>
	struct overload_member_caster_helper<PP::cv_qualifier::volatile_, PP::ref_qualifier::lvalue, Args...>
	{
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) volatile&) const noexcept { return x; }
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) volatile& noexcept) const noexcept { return x; }
	};
	template <typename... Args>
	struct overload_member_caster_helper<PP::cv_qualifier::const_volatile, PP::ref_qualifier::lvalue, Args...>
	{
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) const volatile&) const noexcept { return x; }
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) const volatile& noexcept) const noexcept { return x; }
	};
	template <typename... Args>
	struct overload_member_caster_helper<PP::cv_qualifier::none, PP::ref_qualifier::rvalue, Args...>
	{
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) &&) const noexcept { return x; }
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) && noexcept) const noexcept { return x; }
	};
	template <typename... Args>
	struct overload_member_caster_helper<PP::cv_qualifier::const_, PP::ref_qualifier::rvalue, Args...>
	{
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) const&&) const noexcept { return x; }
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) const&& noexcept) const noexcept { return x; }
	};
	template <typename... Args>
	struct overload_member_caster_helper<PP::cv_qualifier::volatile_, PP::ref_qualifier::rvalue, Args...>
	{
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) volatile&&) const noexcept { return x; }
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) volatile&& noexcept) const noexcept { return x; }
	};
	template <typename... Args>
	struct overload_member_caster_helper<PP::cv_qualifier::const_volatile, PP::ref_qualifier::rvalue, Args...>
	{
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) const volatile&&) const noexcept { return x; }
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) const volatile&& noexcept) const noexcept { return x; }
	};
}

template <typename... Args>
constexpr inline detail::overload_caster_helper<Args...> overload_caster = {};

template <PP::cv_qualifier cv, PP::ref_qualifier ref, typename... Args>
constexpr inline detail::overload_member_caster_helper<cv, ref, Args...> overload_member_caster = {};
