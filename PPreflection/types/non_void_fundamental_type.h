#pragma once
#include "named_type.h"
#include "non_array_object_type.h"
#include "non_user_defined_type.h"

namespace PPreflection
{
	class dynamic_object;

	class non_void_fundamental_type : public detail::named_type<detail::non_user_defined_type<non_array_object_type>>
	{
	public:
		constexpr void destroy(void*) const noexcept override final
		{}

		virtual dynamic_object create_instance() const noexcept = 0;
	};
}
