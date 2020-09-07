#pragma once
#include "overloaded_maybe_static_member_function.h"

class member_function;
class overloaded_conversion_function;

class overloaded_member_function : public detail::overloaded_maybe_static_member_function
{
protected:
	constexpr virtual any_view<const member_function&> get_member_function_overloads() const noexcept = 0;

public:
	constexpr dynamic_object invoke(dynamic_reference caller, pointer_view<const dynamic_reference> args = {}) const;

	constexpr virtual const overloaded_conversion_function* is_conversion_function() const noexcept
	{
		return nullptr;
	}

	constexpr PP::view auto get_overloads() const noexcept
	{
		return get_member_function_overloads();
	}
};
