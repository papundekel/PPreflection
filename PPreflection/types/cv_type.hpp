#pragma once
#include "cv_type.h"

#include "../parent_descriptor_reference.h"

template <typename Type>
constexpr PPreflection::parent_descriptor_reference
PPreflection::cv_type<Type>::get_parent(void*) const noexcept
{
	return type.get_parent();
}
