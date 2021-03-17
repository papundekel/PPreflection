#pragma once
#include "PP/view.hpp"

#include "maybe_static_member_function.h"

namespace PPreflection
{
	class constructor : public detail::maybe_static_member_function
	{
	public:
		constexpr virtual bool is_explicit() const noexcept = 0;

		constexpr bool is_converting() const noexcept
		{
			return !is_explicit() && PP::view_count(parameter_types()) == 1;
		}
	};
}
