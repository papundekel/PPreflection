#pragma once
#include "function.h"
#include "overloaded_maybe_static_member_function.h"

class type;

namespace detail
{
	class maybe_static_member_function : public function
	{
	public:
		constexpr const overloaded_maybe_static_member_function& get_overloaded_function() const noexcept override = 0;

		constexpr const type& get_parent() const noexcept override final;
	};
}
