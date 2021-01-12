#pragma once
#include <variant>
#include "dynamic_object.h"
#include "dynamic_reference.h"
#include "../PP/PP/overloaded.hpp"

class dynamic_variable
{
	friend class dynamic_reference;
	
	std::variant<dynamic_reference, dynamic_object> dynamic;

	explicit dynamic_variable(dynamic_reference r)
		: dynamic(std::move(r))
	{}
	explicit dynamic_variable(dynamic_object o)
		: dynamic(std::move(o))
	{}

public:
	template <typename F>
	static auto create(F&& f)
	{
		using R = decltype(std::forward<F>(f)());

		if constexpr (std::is_void_v<R>)
		{
			std::forward<F>(f)();
			return dynamic_variable(dynamic_object::create_void());
		}
		else if constexpr (std::is_reference_v<R>)
			return dynamic_variable(dynamic_reference(std::forward<F>(f)()));
		else
			return dynamic_variable(dynamic_object(std::forward<F>(f)));
	}
	explicit operator bool() const noexcept
	{
		return std::visit(PP::overloaded{
			[](const dynamic_reference&)
			{
				return true;
			},
			[](const dynamic_object& o)
			{
				return (bool)o;
			} }, dynamic);
	}
	dynamic_object::invalid_code get_error_code() const noexcept
	{
		return std::visit(PP::overloaded{
			[](const dynamic_reference&)
			{
				return dynamic_object::invalid_code::none;
			},
			[](const dynamic_object& o)
			{
				return o.get_error_code();
			} }, dynamic);
	}
	static auto create_invalid(dynamic_object::invalid_code code) noexcept
	{
		return dynamic_variable(dynamic_object::create_invalid(code));
	}
	decltype(auto) get_type() const noexcept
	{
		return std::visit([](const auto& r) -> const type& { return r.get_type(); }, dynamic);
	}
	operator dynamic_reference() const noexcept
	{
		return std::visit(PP::overloaded{
			[](const dynamic_reference& r)
			{
				return r;
			},
			[](const dynamic_object& o) -> dynamic_reference
			{
				return o;
			} }, dynamic);
	}
};
