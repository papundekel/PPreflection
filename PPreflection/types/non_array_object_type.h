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
		constexpr PP::variant<
			const known_bound_array_type&,
			const non_array_object_type&> cast_down(PP::overload_tag<complete_object_type>) const noexcept override final
		{
			return {PP::placeholder, *this};
		}
		constexpr virtual PP::variant<
			const non_void_fundamental_type&,
			const pointer_type&,
			const pointer_to_member_type&,
			const user_defined_type&> cast_down(PP::overload_tag<non_array_object_type> = {}) const noexcept = 0;

		constexpr virtual standard_conversion_sequence make_standard_conversion_sequence_impl(const non_array_object_type& target) const noexcept = 0;
		constexpr standard_conversion_sequence make_standard_conversion_sequence(const non_array_object_type& target) const noexcept override final;
	};
}
