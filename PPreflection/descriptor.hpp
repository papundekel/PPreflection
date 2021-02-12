#pragma once
#include "descriptor.h"
#include "reflect.h"

constexpr std::string_view PPreflection::descriptor::reflect_name(PP::concepts::type auto t) noexcept
{
	return reflect(PP::type<tags::name<PP_GET_TYPE(t)>>);
}
