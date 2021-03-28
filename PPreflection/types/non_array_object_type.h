#pragma once
#include "complete_object_type.h"

namespace PPreflection
{
	class non_void_fundamental_type;
	class pointer_type;
	class pointer_to_member_type;
	class user_defined_type;

	class non_array_object_type : public complete_object_type
	{
	public:
		constexpr PP::type_disjunction_reference<
			known_bound_array_type,
			non_array_object_type> cast_down(PP::overload_tag<complete_object_type>) const noexcept override final
		{
			return *this;
		}
		constexpr virtual PP::type_disjunction_reference<
			non_void_fundamental_type,
			pointer_type,
			pointer_to_member_type,
			user_defined_type> cast_down(PP::overload_tag<non_array_object_type> = {}) const noexcept = 0;

		constexpr bool can_be_initialized(const reference_type&) const noexcept
		{
			return true; /* TODO */
		}

		constexpr virtual standard_conversion_sequence make_standard_conversion_sequence(const non_array_object_type& target) const noexcept = 0;
		constexpr standard_conversion_sequence make_standard_conversion_sequence(const non_array_object_type& target, void*) const noexcept override final;
	};
}
