#pragma once
#include "basic_overloaded_member_function.h"

class overloaded_conversion_function;

namespace detail
{
	template <typename ID, typename Functions>
	class basic_overloaded_conversion_function : public basic_overloaded_member_function_base<ID, Functions, overloaded_conversion_function>
	{
		constexpr pointer_view<const cref_t<conversion_function>> get_conversion_overloads() const noexcept override final
		{
			return reflect_many<Functions, conversion_function>();
		}
	};
}
