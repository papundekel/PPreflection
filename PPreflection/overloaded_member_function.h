#pragma once
#include "overloaded_maybe_static_member_function.h"

class member_function;
class overloaded_conversion_function;

class overloaded_member_function : public detail::overloaded_maybe_static_member_function
{
protected:
	constexpr virtual pointer_view<const cref_t<member_function>> get_member_function_overloads() const noexcept = 0;

public:
	constexpr PP::view auto get_overloads() const noexcept
	{
		return get_overloads_helper<member_function>(get_member_function_overloads());
	}
	constexpr dynamic_object invoke(dynamic_reference caller, pointer_view<const dynamic_reference> args = {}) const;

	constexpr virtual const overloaded_conversion_function* is_conversion_function() const noexcept
	{
		return nullptr;
	}
};
