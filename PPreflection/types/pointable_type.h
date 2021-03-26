#pragma once
#include "PP/cv_qualifier.hpp"

#include "type.h"

namespace PPreflection
{
	class dynamic_pointer_type;
	class referencable_type;
	class void_type;

	class pointable_type : public type
	{
	public:
		constexpr PP::type_disjunction_reference<reference_type, pointable_type> cast_down(PP::overload_tag<type>) const noexcept override final
		{
			return *this;
		}
		constexpr virtual PP::type_disjunction_reference<void_type, referencable_type> cast_down(PP::overload_tag<pointable_type> = {}) const noexcept = 0;

		constexpr bool can_be_pointer_initialized(const pointable_type&) const noexcept
		{
			return true; // TODO
		}

		constexpr dynamic_pointer_type make_pointer(PP::cv_qualifier cv) const noexcept;
	};
}
