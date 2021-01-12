#pragma once
#include "class_type.h"
#include "../functions/constructor.h"

inline dynamic_variable class_type::create_instance(pointer_view<const dynamic_reference> args) const noexcept
{
	return get_constructors().invoke(args);
}
