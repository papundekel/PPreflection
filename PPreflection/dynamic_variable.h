#pragma once
#include <variant>

#include "concepts/reference.hpp"
#include "concepts/void.hpp"
#include "dynamic_object.h"
#include "dynamic_reference.h"
#include "overloaded.hpp"

namespace PPreflection
{
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
		static auto create(auto&& f)
		{
			constexpr auto result_type = PP_DECLTYPE(PP_FORWARD(f)());

			if constexpr (PP::is_void(result_type))
			{
				PP_FORWARD(f)();
				return dynamic_variable(dynamic_object::create_void());
			}
			else if constexpr (PP::is_reference(result_type))
				return dynamic_variable(dynamic_reference(PP_FORWARD(f)()));
			else
				return dynamic_variable(dynamic_object(PP_FORWARD(f)));
		}
		explicit operator bool() const noexcept
		{
			return std::visit(PP::overloaded
			(
				[](const dynamic_reference&)
				{
					return true;
				},
				[](const dynamic_object& o)
				{
					return (bool)o;
				}
			), dynamic);
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
			return std::visit(PP::overloaded
			(
				[](const dynamic_reference& r)
				{
					return r;
				},
				[](const dynamic_object& o) -> dynamic_reference
				{
					return o;
				}
			), dynamic);
		}
	};
}
