#pragma once
#include "non_array_object_type.h"

class parent_descriptor_reference;

class user_defined_type : public non_array_object_type
{
public:
	constexpr virtual parent_descriptor_reference get_parent() const noexcept = 0;
	constexpr const descriptor* get_parent_implementation() const noexcept override final;
};
