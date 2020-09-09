#pragma once
#include "non_array_object_type.h"

class pointer_type : public non_array_object_type
{
public:
	constexpr virtual const pointable_type& remove_pointer() const noexcept = 0;
};
