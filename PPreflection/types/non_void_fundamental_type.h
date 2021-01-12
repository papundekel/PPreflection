#pragma once
#include "non_array_object_type.h"
#include "non_user_defined_type.h"

class non_void_fundamental_type : public detail::non_user_defined_type<non_array_object_type>
{
	constexpr void destroy(void* ptr) const noexcept override final
	{}
};
