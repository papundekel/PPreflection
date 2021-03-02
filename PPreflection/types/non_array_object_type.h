#pragma once
#include "complete_object_type.h"

namespace PPreflection
{
	class non_array_object_type : public complete_object_type
	{
	public:
		constexpr bool can_be_initialized(const reference_type&) const noexcept
		{
			return true; /* TODO */
		}
	};
}
