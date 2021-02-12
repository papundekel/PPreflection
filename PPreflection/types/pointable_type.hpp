#pragma once
#include "pointable_type.h"
#include "dynamic_pointer_type.h"

constexpr PPreflection::dynamic_pointer_type PPreflection::pointable_type::make_pointer() const noexcept
{
	return dynamic_pointer_type(*this);
}
