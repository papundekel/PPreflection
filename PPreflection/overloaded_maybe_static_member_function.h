#pragma once
#include "overloaded_function.h"

namespace detail
{
	class overloaded_maybe_static_member_function : public overloaded_function
	{
	public:
		constexpr const type& get_parent() const noexcept override = 0;
	};
}
