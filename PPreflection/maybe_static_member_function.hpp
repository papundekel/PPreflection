#pragma once
#include "maybe_static_member_function.h"
#include "overloaded_maybe_static_member_function.h"

constexpr const type& detail::maybe_static_member_function::get_enclosing_class() const noexcept
{
	return get_overloaded_function().get_enclosing_class();
}
