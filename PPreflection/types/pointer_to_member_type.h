#pragma once
#include "non_array_object_type.h"
#include "non_user_defined_type.h"

namespace PPreflection
{
	class pointer_to_member_type : public detail::non_user_defined_type<non_array_object_type>
	{

	};
}
