#pragma once
#include "class_type.h"
#include "../functions/constructor.h"

inline PPreflection::dynamic_variable PPreflection::class_type::create_instance(PP::any_view_ra<const dynamic_reference&> args) const noexcept
{
	return get_constructors().invoke(args);
}
