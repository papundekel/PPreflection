#pragma once
#include "overloaded_maybe_static_member_function.h"
#include "../PP/PP/transform_view.hpp"
#include "../PP/PP/id.hpp"

class constructor;

class overloaded_constructor : public overloaded_maybe_static_member_function
{
protected:
	constexpr virtual pointer_view<const cref_t<constructor>> get_constructor_overloads() const noexcept = 0;

public:
	constexpr PP::view auto get_overloads() const noexcept
	{
		return get_overloads_helper<constructor>(get_constructor_overloads());
	}
};
