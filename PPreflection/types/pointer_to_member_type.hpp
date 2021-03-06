#pragma once
#include "class_type.h"
#include "pointer_to_member_type.h"

constexpr bool PPreflection::pointer_to_member_type::operator==(const pointer_to_member_type& other) const noexcept
{
	return
		get_class_type() == other.get_class_type() && 
		get_member_type() == other.get_member_type();
}
