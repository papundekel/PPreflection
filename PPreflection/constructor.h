#pragma once
#include "maybe_static_member_function.h"
#include "overloaded_constructor.h"

class constructor : public detail::maybe_static_member_function
{
public:
	constexpr const overloaded_constructor& get_overloaded_function() const noexcept override = 0;

	constexpr virtual bool is_explicit() const noexcept = 0;
};
