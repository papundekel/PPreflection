#pragma once
#include "overloaded_function.h"
#include "function.h"
#include "map_pack.h"

constexpr dynamic_object overloaded_function::invoke(pointer_view<const dynamic_reference> args) const
{
	for (const function& f : get_overloads())
		if (f.can_invoke(args))
			return f.invoke_unsafe(args);

	return dynamic_object::create_invalid();
}
