#pragma once
#include "overloaded_function.h"

template <typename Function>
class overloaded_member_like_function : public overloaded_function<Function>
{
public:
	constexpr virtual const type& get_enclosing_class() const noexcept = 0;
};
