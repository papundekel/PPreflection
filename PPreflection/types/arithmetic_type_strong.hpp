#pragma once
#include "arithmetic_type_strong.h"

#include "../dynamic_object.h"
#include "make_numeric_conversion.hpp"

template <typename T>
inline PPreflection::dynamic_object
PPreflection::arithmetic_type_strong<T>::create_instance() const noexcept
{
	return dynamic_object::create(PP::type<T>);
}

template <typename T>
constexpr PPreflection::convertor_object
PPreflection::arithmetic_type_strong<T>::conversion(
	const arithmetic_type& target) const noexcept
{
	return make_numeric_conversion(PP::type<T>, target);
}
