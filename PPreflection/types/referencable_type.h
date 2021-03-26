#pragma once
#include "PP/get_value.hpp"

#include "pointable_type.h"

namespace PPreflection
{
	class function_type;
	class object_type;
	class implicit_conversion_sequence;
	class non_array_object_type;
	
	class referencable_type : public pointable_type
	{
	public:
		constexpr PP::type_disjunction_reference<void_type, referencable_type> cast_down(PP::overload_tag<pointable_type>) const noexcept override final
		{
			return *this;
		}
		constexpr virtual PP::type_disjunction_reference<function_type, object_type> cast_down(PP::overload_tag<referencable_type> = {}) const noexcept = 0;

		constexpr virtual implicit_conversion_sequence make_conversion_sequence(const non_array_object_type& target) const noexcept = 0;
	};
}
