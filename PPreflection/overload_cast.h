#pragma once
#include "cv_qualifier.h"
#include "ref_qualifier.h"
#include "add_function_cvrefn.h"

namespace detail
{
	template <typename... Args>
	struct overload_caster_helper
	{
		template <typename Return>
		constexpr auto& operator()(Return(&x)(Args...)) const noexcept { return x; }
	};

	template <cv_qualifier cv, ref_qualifier ref, typename... Args>
	struct overload_member_caster_helper
	{
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...)) const noexcept { return x; }
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) noexcept) const noexcept { return x; }
	};
	template <typename... Args>
	struct overload_member_caster_helper<cv_qualifier::const_, ref_qualifier::none, Args...>
	{
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) const) const noexcept { return x; }
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) const noexcept) const noexcept { return x; }
	};
	template <typename... Args>
	struct overload_member_caster_helper<cv_qualifier::volatile_, ref_qualifier::none, Args...>
	{
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) volatile) const noexcept { return x; }
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) volatile noexcept) const noexcept { return x; }
	};
	template <typename... Args>
	struct overload_member_caster_helper<cv_qualifier::const_volatile, ref_qualifier::none, Args...>
	{
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) const volatile) const noexcept { return x; }
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) const volatile noexcept) const noexcept { return x; }
	};
	template <typename... Args>
	struct overload_member_caster_helper<cv_qualifier::none, ref_qualifier::lvalue, Args...>
	{
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) &) const noexcept { return x; }
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) & noexcept) const noexcept { return x; }
	};
	template <typename... Args>
	struct overload_member_caster_helper<cv_qualifier::const_, ref_qualifier::lvalue, Args...>
	{
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) const&) const noexcept { return x; }
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) const& noexcept) const noexcept { return x; }
	};
	template <typename... Args>
	struct overload_member_caster_helper<cv_qualifier::volatile_, ref_qualifier::lvalue, Args...>
	{
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) volatile&) const noexcept { return x; }
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) volatile& noexcept) const noexcept { return x; }
	};
	template <typename... Args>
	struct overload_member_caster_helper<cv_qualifier::const_volatile, ref_qualifier::lvalue, Args...>
	{
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) const volatile&) const noexcept { return x; }
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) const volatile& noexcept) const noexcept { return x; }
	};
	template <typename... Args>
	struct overload_member_caster_helper<cv_qualifier::none, ref_qualifier::rvalue, Args...>
	{
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) &&) const noexcept { return x; }
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) && noexcept) const noexcept { return x; }
	};
	template <typename... Args>
	struct overload_member_caster_helper<cv_qualifier::const_, ref_qualifier::rvalue, Args...>
	{
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) const&&) const noexcept { return x; }
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) const&& noexcept) const noexcept { return x; }
	};
	template <typename... Args>
	struct overload_member_caster_helper<cv_qualifier::volatile_, ref_qualifier::rvalue, Args...>
	{
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) volatile&&) const noexcept { return x; }
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) volatile&& noexcept) const noexcept { return x; }
	};
	template <typename... Args>
	struct overload_member_caster_helper<cv_qualifier::const_volatile, ref_qualifier::rvalue, Args...>
	{
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) const volatile&&) const noexcept { return x; }
		template <typename Return, typename Class>
		constexpr auto operator()(Return(Class::* x)(Args...) const volatile&& noexcept) const noexcept { return x; }
	};
}

template <typename... Args>
constexpr inline detail::overload_caster_helper<Args...> overload_caster = {};

template <cv_qualifier cv, ref_qualifier ref, typename... Args>
constexpr inline detail::overload_member_caster_helper<cv, ref, Args...> overload_member_caster = {};
