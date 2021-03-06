#pragma once
#include "arithmetic_type_strong.h"

#include "../dynamic_object.h"

template <typename T>
inline PPreflection::dynamic_object PPreflection::arithmetic_type_strong<T>::create_instance() const noexcept
{
	return dynamic_object::create(PP::type<T>);
}
