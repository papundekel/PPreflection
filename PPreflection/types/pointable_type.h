#pragma once
#include "PP/cv_qualifier.hpp"

#include "type.h"

namespace PPreflection
{
	class dynamic_pointer_type;

	class pointable_type : public type
	{
	public:
		constexpr type_disjunction_reference<reference_type, pointable_type> reference_or_pointable() const noexcept override final
		{
			return *this;
		}

		constexpr bool can_be_pointer_initialized(const pointable_type&) const noexcept
		{
			return true; // TODO
		}

		constexpr dynamic_pointer_type make_pointer(PP::cv_qualifier cv) const noexcept;
	};
}
