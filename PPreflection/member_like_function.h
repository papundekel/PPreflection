#pragma once
#include "member_like_function_base.h"

template <typename T>
class overloaded_member_like_function;

class member_like_function : public member_like_function_base
{
public:
	constexpr const type& get_enclosing_class() const noexcept override final;

	constexpr virtual const overloaded_member_like_function<member_like_function>& get_overloaded_function() const noexcept = 0;
};
