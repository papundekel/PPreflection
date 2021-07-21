#pragma once
#include "../class_or_namespace.h"
#include "../parent_descriptor.h"
#include "named_type.h"
#include "non_array_object_type.h"

namespace PPreflection
{
///
/// @brief Represents a user defined type.
///
class user_defined_type : public detail::named_type<non_array_object_type>
{
public:
	///
	/// @brief Gets the parent entity.
	///
	/// @return Either a namespace or a class.
	///
	constexpr virtual class_or_namespace get_parent(int = 0) const noexcept = 0;

	///
	/// @brief Compares two user defined types.
	///
	constexpr bool operator==(const user_defined_type& other) const noexcept
	{
		return this == &other;
	}

	constexpr bool operator==(const type& other) const noexcept override final
	{
		return compare(*this, other);
	}

private:
	constexpr virtual parent_descriptor get_parent(
		void*) const noexcept override final
	{
		return PP::visit(
			[](const auto& t)
			{
				return parent_descriptor(t);
			},
			get_parent());
	}

	constexpr PP::variant<const non_void_fundamental_type&,
	                      const pointer_type&,
	                      const pointer_to_member_type&,
	                      const user_defined_type&>
		cast_down(PP::overload_tag<non_array_object_type>)
			const noexcept override final
	{
		return {PP::placeholder, *this};
	}
};
}
