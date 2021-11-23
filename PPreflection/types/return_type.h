#pragma once
#include "PP/static_cast.hpp"
#include "PP/variant.hpp"

#include "make_equal_operator_visitor.h"
#include "non_array_object_type.h"
#include "reference_type.h"
#include "void_type.h"

namespace PPreflection
{
namespace detail
{
using return_type_base = PP::variant<const reference_type&,
                                     const non_array_object_type&,
                                     const void_type&>;
}

///
/// @brief Represents a type which be returned from a function.
///
class return_type : public detail::return_type_base
{
public:
	///
	/// @brief Constructs a reference return type.
	///
	constexpr return_type(const reference_type& t)
		: detail::return_type_base(PP::placeholder, t)
	{}

	///
	/// @brief Constructs a value return type.
	///
	constexpr return_type(const non_array_object_type& t)
		: detail::return_type_base(PP::placeholder, t)
	{}

	///
	/// @brief Constructs a @p void return type.
	///
	constexpr return_type(const void_type& t)
		: detail::return_type_base(PP::placeholder, t)
	{}

	///
	/// @brief Converts to a type descriptor.
	///
	constexpr const type& as_type() const noexcept
	{
		return PP::visit(PP::static__cast * PP::type<const type&>, *this);
	}

	///
	/// @brief Converts to a type descriptor.
	///
	constexpr operator const type&() const noexcept
	{
		return as_type();
	}

	///
	/// @brief Compares two return types.
	///
	/// @retval true iff the two return types are the same type.
	///
	constexpr bool operator==(return_type other) const noexcept
	{
		return PP::visit(make_equal_operator_visitor(other), *this);
	}
};
}
