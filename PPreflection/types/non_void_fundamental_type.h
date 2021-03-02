#pragma once
#include "non_array_object_type.h"
#include "non_user_defined_type.h"

namespace PPreflection
{
	class non_void_fundamental_type : public detail::named_descriptor<detail::non_user_defined_type<non_array_object_type>>
	{
		constexpr void destroy(void*) const noexcept override final
		{}
	};
}
