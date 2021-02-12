#pragma once
#include "dynamic_specific_reference_type_base.h"

namespace PPreflection
{
	class dynamic_rvalue_reference_type final : public detail::dynamic_specific_reference_type_base
	{
	public:
		using dynamic_specific_reference_type_base::dynamic_specific_reference_type_base;

		constexpr bool is_lvalue() const noexcept override final
		{
			return false;
		}
	};
}
