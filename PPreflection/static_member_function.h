#pragma once
#include "maybe_static_member_function.h"
#include "overloaded_static_member_function.h"

class static_member_function : public maybe_static_member_function 
{
	constexpr const overloaded_static_member_function& get_overloaded_function() const noexcept override = 0;
};
