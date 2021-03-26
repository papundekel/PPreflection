#pragma once
#include "PP/cv_qualifier.hpp"
#include "PP/size_t.hpp"

#include "referencable_type.h"

namespace PPreflection
{
	class complete_object_type;
	class unknown_bound_array_type;

	class object_type : public referencable_type
	{
	public:
		constexpr PP::type_disjunction_reference<function_type, object_type> cast_down(PP::overload_tag<referencable_type>) const noexcept override final
		{
			return *this;
		}
		constexpr virtual PP::type_disjunction_reference<unknown_bound_array_type, complete_object_type> cast_down(PP::overload_tag<object_type> = {}) const noexcept = 0;

		constexpr virtual PP::size_t alignment() const noexcept = 0;
	};
}
