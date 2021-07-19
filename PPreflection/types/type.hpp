#pragma once
#include "type.h"

#include "../reflect.h"

constexpr auto PPreflection::type::reflect_helper(
	PP::concepts::type auto t) noexcept -> const
	PP_APPLY_TRANSFORM(get_class, t) &
{
	return PPreflection::reflect_descriptor(t);
}
constexpr auto PPreflection::type::reflect_cv_helper(
	PP::concepts::type auto t) noexcept
	-> PPreflection::cv_type<
		PP_GT(~PP_DECLTYPE(PPreflection::type::reflect_helper(t)))>
{
	const auto& tt = reflect_helper(t);
	auto cv = *PP::get_cv_value_t(t);

	return cv_type{tt, cv};
}
