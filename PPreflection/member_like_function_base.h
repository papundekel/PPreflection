#pragma once
#include "function.h"

class type;

class member_like_function_base : public function
{
public:
	constexpr virtual const type& get_enclosing_class() const noexcept = 0;
};
