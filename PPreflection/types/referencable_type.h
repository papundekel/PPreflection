#pragma once
#include "PP/get_value.hpp"

#include "pointable_type.h"

namespace PPreflection
{
	class function_type;
	class object_type;
	class standard_conversion_sequence;
	class non_array_object_type;

	class referencable_type : public pointable_type
	{
	public:
		constexpr PP::variant<const void_type&, const referencable_type&>
			cast_down(
				PP::overload_tag<pointable_type>) const noexcept override final
		{
			return { PP::placeholder, *this };
		}
		constexpr virtual PP::variant<const function_type&, const object_type&>
			cast_down(
				PP::overload_tag<referencable_type> = {}) const noexcept = 0;

		constexpr virtual standard_conversion_sequence
		make_standard_conversion_sequence(
			const non_array_object_type& target) const noexcept = 0;
	};
}
