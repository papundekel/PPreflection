#pragma once
#include "type.h"
#include "types.h"
#include "../reflect.h"
#include <type_traits>

constexpr auto PPreflection::type::reflect_helper(PP::concepts::type auto t) noexcept -> const PP_APPLY_TRANSFORM(get_class, t)&
{
	return PPreflection::reflect(t);
}
