#pragma once
#include "non_array_object_type.h"
#include "non_user_defined_type.h"

namespace PPreflection
{
	class class_type;

	class pointer_to_member_type : public detail::non_user_defined_type<non_array_object_type>
	{
	public:
		constexpr virtual const class_type& get_class_type() const noexcept = 0;
		constexpr virtual cv_type<referencable_type> get_member_type() const noexcept = 0;

		constexpr bool operator==(const pointer_to_member_type& other) const noexcept;
		constexpr bool operator==(const type& other) const noexcept override final
		{
			return compare(*this, other);
		}
	};
}
