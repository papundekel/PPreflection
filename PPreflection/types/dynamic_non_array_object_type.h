#pragma once
#include "non_array_object_type.h"
#include "dynamic_cv_qualifiable_type.h"

namespace PPreflection
{
	class dynamic_non_array_object_type : public dynamic_cv_qualifiable_type<non_array_object_type>
	{
	public:
		using dynamic_cv_qualifiable_type<non_array_object_type>::dynamic_cv_qualifiable_type;
	};
}
