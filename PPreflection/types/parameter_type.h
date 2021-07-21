#pragma once
#include "PP/static_cast.hpp"
#include "PP/variant.hpp"

#include "make_equal_operator_visitor.h"
#include "non_array_object_type.h"
#include "reference_type.h"

namespace PPreflection
{
namespace detail
{
using parameter_type_base =
	PP::variant<const reference_type&, const non_array_object_type&>;
}

///
/// @brief Represents a type which can serve as a paramater type in a function.
///
class parameter_type : public detail::parameter_type_base
{
public:
	///
	/// @brief Constructs a reference parameter type.
	///
	constexpr parameter_type(const reference_type& t)
		: detail::parameter_type_base(PP::placeholder, t)
	{}

	///
	/// @brief Constructs a value parameter type.
	///
	constexpr parameter_type(const non_array_object_type& t)
		: detail::parameter_type_base(PP::placeholder, t)
	{}

	///
	/// @brief Converts to type descriptor.
	///
	constexpr const type& to_type() const
	{
		return PP::visit(PP::static__cast * PP::type<const type&>, *this);
	}

	///
	/// @brief Converts to type descriptor.
	///
	constexpr operator const type&() const
	{
		return to_type();
	}

	///
	/// @brief Converts to type descriptor pointer.
	///
	constexpr const type* operator&() const
	{
		return &(const type&)*this;
	}

	///
	/// @brief Compares two parameter types.
	///
	/// @retval true iff the two parameter types are the same type.
	///
	constexpr bool operator==(parameter_type other) const noexcept
	{
		return PP::visit(make_equal_operator_visitor(other), *this);
	}
};
}
