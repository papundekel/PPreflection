#pragma once
#include "function.h"
#include "../types/class_type.h"

namespace detail
{
	class overloaded_maybe_static_member_function : public function::overloaded
	{
	public:
		constexpr const class_type& get_parent() const noexcept override = 0;
	};

	class maybe_static_member_function : public function
	{
	public:
		using overloaded = overloaded_maybe_static_member_function;

		constexpr const overloaded& get_overloaded_function() const noexcept override = 0;

		constexpr const class_type& get_parent() const noexcept override final
		{
			return get_overloaded_function().get_parent();
		}
	};
}
