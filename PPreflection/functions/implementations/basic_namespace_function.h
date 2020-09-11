#pragma once
#include "../namespace_function.h"
#include "basic_static_function.h"

namespace detail
{
	template <typename Overload, auto f>
	class basic_namespace_function : public basic_static_function<Overload, f, namespace_function>
	{};
}
