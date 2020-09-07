#pragma once
#include "overloaded_maybe_static_member_function.h"

class static_member_function;

class overloaded_static_member_function : public detail::overloaded_maybe_static_member_function
{
protected:
	constexpr virtual any_view<const static_member_function&> get_static_member_overloads() const noexcept = 0;

public:
	constexpr PP::view auto get_overloads() const noexcept
	{
		return get_static_member_overloads();
	}
};
