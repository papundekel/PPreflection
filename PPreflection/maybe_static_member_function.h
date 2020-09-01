#pragma once
#include "function.h"

class type;

class maybe_static_member_function : public function
{
public:
	constexpr virtual const type& get_enclosing_class() const noexcept = 0;
};
