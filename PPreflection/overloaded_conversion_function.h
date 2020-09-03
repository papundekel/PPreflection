#pragma once
#include "overloaded_member_function.h"

class conversion_function;

class overloaded_conversion_function : public overloaded_member_function
{
	constexpr virtual pointer_view<const cref_t<conversion_function>> get_conversion_overloads() const noexcept = 0;

public:
	constexpr dynamic_object invoke(dynamic_reference caller) const;

	constexpr const overloaded_conversion_function* is_conversion_function() const noexcept override final
	{
		return this;
	}
	constexpr PP::view auto get_overloads() const noexcept
	{
		return get_overloads_helper<conversion_function>(get_conversion_overloads());
	}
};
