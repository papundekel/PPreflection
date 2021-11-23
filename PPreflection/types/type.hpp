#pragma once
#include "type.h"

#include "../reflect.h"

constexpr auto PPreflection::detail::type_helper::reflect_helper(
	PP::concepts::type auto t) noexcept -> const
	PP_APPLY_TRANSFORM(get_class, t) &
{
	return reflect_descriptor(t);
}
constexpr auto PPreflection::detail::type_helper::reflect_cv_helper(
	PP::concepts::type auto t) noexcept
	-> PP_GT(PP::Template<cv_type>(~PP_DECLTYPE(reflect_helper(t))))
{
	return {reflect_helper(t), *PP::get_cv_value_t(t)};
}
