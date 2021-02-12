#pragma once
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

		constexpr bool can_be_pointer_initialized(const pointable_type& initializer) const noexcept
		{
			return true;
		}

		constexpr dynamic_pointer_type make_pointer() const noexcept;
	};
}
