#pragma once
#include "user_defined_type.h"
#include "../parent_descriptor_reference.h"

constexpr const descriptor* user_defined_type::get_parent_implementation() const noexcept
{
	return &(const descriptor&)get_parent();
}
