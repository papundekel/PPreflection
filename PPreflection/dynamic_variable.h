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
	///
	/// @brief A dynamic variable. A disjunction of the dynamic reference and
	/// the dynamic object. Can hold either of the two.
	///
	class dynamic_variable
	{
		friend class dynamic_reference;
		friend class constructor;

		std::variant<dynamic_reference, dynamic_object> dynamic;

	public:
		///
		/// @brief Construct a reference variable.
		///
		explicit constexpr dynamic_variable(dynamic_reference r)
			: dynamic(r)
		{}

		///
		/// @brief Construct an object variable. moves
		///
		explicit constexpr dynamic_variable(dynamic_object&& o)
			: dynamic(PP::move(o))
		{}

		///
		/// @brief Move constructor. Moves the internal reference or object.
		///
		dynamic_variable(dynamic_variable&&) = default;

		///
		/// @brief Move Assignment. Moves the internal reference or object.
		///
		dynamic_variable& operator=(dynamic_variable&&) = default;

		///
		/// @brief Initializes the variable with a no-argument call to @p f.
		/// Deduces the kind and type of the variable from the return type.
		///
		static constexpr auto create(auto&& f)
		{
			constexpr auto result_type = PP_DECLTYPE(PP_F(f)());

			if constexpr (PP::is_void(result_type))
			{
				PP_F(f)();
				return dynamic_variable(dynamic_object::create_void());
			}
			else if constexpr (PP::is_reference(result_type))
				return dynamic_variable(dynamic_reference(PP_F(f)()));
			else
				return dynamic_variable(dynamic_object(PP_F(f)));
		}

		///
		/// @brief Validity check.
		///
		/// @retval true iff this is a reference variable or an object variable
		/// not in the @p invalid state.
		///
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

		///
		/// @brief Gets the error code.
		///
		/// @retval none iff this is a reference variable or an object variable
		/// not in the @p invalid state.
		///
		constexpr dynamic_object::invalid_code get_error_code() const noexcept
		{
			return std::visit(
				PP::overloaded{[](const dynamic_reference&)
			                   {
								   return dynamic_object::invalid_code::none;
							   },
			                   [](const dynamic_object& o)
			                   {
								   return o.get_error_code();
							   }},
				dynamic);
		}

		///
		/// @brief Creates an object variable in the @p invalid state with error
		/// code @p code.
		///
		static dynamic_variable create_invalid(
			dynamic_object::invalid_code code) noexcept;

		///
		/// @brief Creates an object variable in the @p void state.
		///
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
		///
		/// @brief Gets the type of the variable.
		///
		/// @return @ref cv_type of @ref type.
		///
		constexpr auto get_type() noexcept
		{
			return std::visit(get_type_helper, dynamic);
		}

		///
		/// @see get_type()
		///
		constexpr auto get_type() const noexcept
		{
			return std::visit(get_type_helper, dynamic);
		}

		///
		/// @brief Creates a dynamic reference to this variable.
		///
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

		///
		/// @brief Calls @ref dynamic_object::move() on object variable or
		/// copies the reference otherwise.
		///
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

		///
		/// @brief Creates a new dynamic object with a move constructor if this
		/// is an object variable. A reference variable returns an object in the
		/// @p void state.
		///
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
