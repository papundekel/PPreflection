#pragma once
#include <utility>
#include "maybe_static_member_function.h"
#include "../types/function_type.h"

class class_type;
class reference_type;
class function_type;

class member_function;

class overloaded_member_function : public detail::maybe_static_member_function::overloaded
{
protected:
	constexpr virtual PP::any_view<const member_function&> get_member_function_overloads() const noexcept = 0;

public:
	inline dynamic_variable invoke(dynamic_reference caller, pointer_view<const dynamic_reference> args = {}) const;

	constexpr PP::view auto get_overloads() const noexcept
	{
		return get_member_function_overloads();
	}
};

class member_function : public detail::maybe_static_member_function
{
	constexpr virtual dynamic_variable invoke_unsafe_member(dynamic_reference caller, PP::any_iterator<const dynamic_reference&> arg_iterator) const = 0;

protected:
	constexpr bool can_invoke(const reference_type& caller_arg_type) const noexcept;

	inline dynamic_variable invoke_unsafe(PP::any_iterator<const dynamic_reference&> arg_iterator) const noexcept override final;
	constexpr  bool can_invoke(PP::any_view<const reference_type&> argument_types) const noexcept override final;

public:
	constexpr void print_name_after_parent(PP::simple_ostream& out) const noexcept override final;
	constexpr bool has_name(std::string_view name) const noexcept override final;
	
	constexpr PP::ref_qualifier get_ref_qualifier() const noexcept
	{
		return get_function_type().get_ref_qualifier();
	}
	constexpr PP::cv_qualifier get_cv_qualifier() const noexcept
	{
		return get_function_type().get_cv_qualifier();
	}

	inline dynamic_variable invoke(dynamic_reference caller, pointer_view<const dynamic_reference> args = {}) const;

	using overloaded = overloaded_member_function;
	friend overloaded_member_function;

	constexpr const overloaded& get_overloaded_function() const noexcept override = 0;

	constexpr const class_type& get_parent() const noexcept override = 0;
};
