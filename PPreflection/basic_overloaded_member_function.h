#pragma once
#include "basic_overloaded_member_function_base.h"

namespace detail
{
	template <typename ID, typename Functions>
	class basic_overloaded_member_function : public basic_overloaded_member_function_base<ID, Functions, overloaded_member_function>
	{};
}
