#pragma once
#include <variant>

#include "PP/concepts/fundamental_types.hpp"
#include "PP/concepts/reference.hpp"
#include "PP/overloaded.hpp"
#include "PP/utility/move.hpp"

#include "dynamic_object.h"
#include "dynamic_reference.h"

namespace PPreflection
{
	class dynamic_variable
	{
		friend class dynamic_reference;
		friend class constructor;

		std::variant<dynamic_reference, dynamic_object> dynamic;

	public:
		explicit constexpr dynamic_variable(dynamic_reference r)
			: dynamic(r)
		{}
		explicit constexpr dynamic_variable(dynamic_object&& o)
			: dynamic(PP::move(o))
		{}

		dynamic_variable(dynamic_variable&&) = default;
		dynamic_variable& operator=(dynamic_variable&&) = default;

		static constexpr auto create(auto&& f)
		{
			constexpr auto result_type = PP_DECLTYPE(PP_FORWARD(f)());

			if constexpr (PP::is_void(result_type))
			{
				PP_FORWARD(f)();
				return dynamic_variable(dynamic_object::create_void());
			} else if constexpr (PP::is_reference(result_type))
				return dynamic_variable(dynamic_reference(PP_FORWARD(f)()));
			else
				return dynamic_variable(dynamic_object(PP_FORWARD(f)));
		}
		constexpr explicit operator bool() const noexcept
		{
			return std::visit(PP::overloaded(
								  [](const dynamic_reference&)
								  {
									  return true;
								  },
								  [](const dynamic_object& o)
								  {
									  return (bool)o;
								  }),
							  dynamic);
		}
		constexpr dynamic_object::invalid_code get_error_code() const noexcept
		{
			return std::visit(
				PP::overloaded{ [](const dynamic_reference&)
								{
									return dynamic_object::invalid_code::none;
								},
								[](const dynamic_object& o)
								{
									return o.get_error_code();
								} },
				dynamic);
		}

		static dynamic_variable create_invalid(
			dynamic_object::invalid_code code) noexcept;
		static dynamic_variable create_void() noexcept;

	private:
		static constexpr auto get_type_helper = PP::overloaded(
			[](const dynamic_reference& r) -> cv_type<type>
			{
				return r.get_type();
			},
			[](const dynamic_object& o) -> cv_type<type>
			{
				return o.get_cv_type();
			},
			[](dynamic_object& o) -> cv_type<type>
			{
				return o.get_cv_type();
			});

	public:
		constexpr auto get_type() noexcept
		{
			return std::visit(get_type_helper, dynamic);
		}
		constexpr auto get_type() const noexcept
		{
			return std::visit(get_type_helper, dynamic);
		}
		constexpr operator dynamic_reference() const noexcept
		{
			return std::visit(
				PP::overloaded(
					[](const dynamic_reference& r)
					{
						return r;
					},
					[](const dynamic_object& o) -> dynamic_reference
					{
						return o;
					}),
				dynamic);
		}
		constexpr dynamic_reference move() const noexcept
		{
			return std::visit(PP::overloaded(
								  [](const dynamic_reference& r)
								  {
									  return r;
								  },
								  [](const dynamic_object& o)
								  {
									  return o.move();
								  }),
							  dynamic);
		}

		constexpr dynamic_object move_object() && noexcept
		{
			return std::visit(PP::overloaded(
								  [](dynamic_reference&)
								  {
									  return dynamic_object::create_void();
								  },
								  [](dynamic_object& o)
								  {
									  return PP::move(o);
								  }),
							  dynamic);
		}
	};
}
