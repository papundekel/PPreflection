#pragma once
#include "non_user_defined_type.h"

#include "../parent_descriptor_reference.h"

template <typename Base>
constexpr PPreflection::parent_descriptor_reference PPreflection::detail::non_user_defined_type<Base>::get_parent(void*) const noexcept
{
	return {};
}
