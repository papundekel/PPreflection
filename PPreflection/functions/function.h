#pragma once
#include <type_traits>
#include "../descriptor.h"
#include "../pointer_view.h"
#include "../dynamic_variable.h"
#include "../../PP/PP/transform_view.hpp"
#include "../../PP/PP/id.hpp"
#include "../../PP/PP/any_iterator.hpp"
#include "../invoke.h"
#include "../types/return_type_reference.h"
#include "../types/function_type.h"

class type;
class dynamic_reference;
class member_function;
class overloaded_function;

class function : public descriptor
{
	friend overloaded_function;

protected:
	constexpr virtual dynamic_variable invoke_unsafe(PP::any_iterator<const dynamic_reference&> arg_iterator) const noexcept = 0;

	constexpr virtual bool can_invoke(PP::any_view<const reference_type&> argument_types) const noexcept;

	template <typename... Parameters>
	struct invoke_helper_t
	{
		class x
		{
			template <typename F, std::size_t... I>
			static constexpr decltype(auto) helper(F&& f, PP::any_iterator<const dynamic_reference&> arg_iterator, std::index_sequence<I...>) noexcept;

		public:
			template <typename F>
			static constexpr decltype(auto) value_f(F&& f, PP::any_iterator<const dynamic_reference&> arg_iterator) noexcept;
		};

		using type = x;
	};

	template <typename ParameterTypes, typename F>
	static constexpr decltype(auto) invoke_helper_helper(F&& f, PP::any_iterator<const dynamic_reference&> arg_iterator) noexcept
	{
		return ::invoke<PP::get_type<PP::apply_pack_types<function::invoke_helper_t, ParameterTypes>>>(std::forward<F>(f), arg_iterator);
	}

	template <typename ParameterTypes, typename F>
	static inline dynamic_variable invoke_helper(F&& f, PP::any_iterator<const dynamic_reference&> arg_iterator) noexcept
	{
		return dynamic_variable::create(
			[&f, arg_iterator]() -> decltype(auto)
			{
				return invoke_helper_helper<ParameterTypes>(std::forward<F>(f), arg_iterator);
			});
	}
	template <typename ReturnType, typename F>
	static inline dynamic_variable invoke_helper(F&& f) noexcept
	{
		return dynamic_variable::create(std::forward<F>(f));
	}

	constexpr void print_name_basic(PP::simple_ostream& out) const noexcept;
	constexpr void print_noexcept(PP::simple_ostream& out) const noexcept;

	constexpr void print_name_before_parent(PP::simple_ostream& out) const noexcept override final;
	constexpr void print_name_after_parent(PP::simple_ostream& out) const noexcept override;

public:
	constexpr bool has_name(std::string_view name) const noexcept override;

	constexpr virtual const function_type& get_function_type() const noexcept = 0;
	constexpr return_type_reference return_type() const noexcept
	{
		return get_function_type().return_type();
	}
	constexpr PP::any_view<parameter_type_reference> parameter_types() const noexcept
	{
		return get_function_type().parameter_types();
	}

	constexpr virtual bool is_noexcept() const noexcept = 0;

	inline dynamic_variable invoke(pointer_view<const dynamic_reference> args = {}) const;


	using overloaded = overloaded_function;

	constexpr virtual const overloaded_function& get_overloaded_function() const noexcept = 0;

	constexpr virtual const descriptor& get_parent() const noexcept;

private:
	constexpr const descriptor* get_parent_implementation() const noexcept override final
	{
		return &get_parent();
	}
};

class overloaded_function : public descriptor
{
protected:
	constexpr virtual PP::any_view<const function&> get_function_overloads() const noexcept = 0;

public:
	constexpr virtual void print_name_before_parent(PP::simple_ostream& out) const noexcept override final
	{}

	inline dynamic_variable invoke(pointer_view<const dynamic_reference> args = {}) const;

	constexpr virtual const descriptor& get_parent() const noexcept = 0;

	template <PP::view View>
	constexpr const function* select_overload(View&& argument_types) const noexcept
	{
		for (const function& f : get_overloads())
			if (f.can_invoke(std::forward<View>(argument_types)))
				return &f;

		return nullptr;
	}

	constexpr PP::view auto get_overloads() const noexcept
	{
		return get_function_overloads();
	}

private:
	constexpr const descriptor* get_parent_implementation() const noexcept override final
	{
		return &get_parent();
	}
};

constexpr const descriptor& function::get_parent() const noexcept
{
	return get_overloaded_function().get_parent();
}
