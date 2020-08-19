#pragma once
#include "member_like_function.h"
#include "overloaded_member_like_function.h"

constexpr const type& member_like_function::get_enclosing_class() const noexcept
{
	return get_overloaded_function().get_enclosing_class();
}
