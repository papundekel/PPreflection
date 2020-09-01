#pragma once
#include "overloaded_function.h"

class overloaded_maybe_static_member_function : public overloaded_function
{
public:
	constexpr virtual const type& get_enclosing_class() const noexcept = 0;
};
