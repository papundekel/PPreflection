#pragma once
#include "overloaded_function.h"
#include "function.h"
#include "map_pack.h"

template <typename Function>
constexpr dynamic_wrap overloaded_function<Function>::invoke(simple_range<const dynamic_ptr> args) const
{
	for (const function& f : get_overloads())
		if (f.can_invoke(args))
			return f.invoke_unsafe(args);

	throw 0;
}
