#pragma once
#include "overloaded_function.h"
#include "function.h"
#include "map_pack.h"

constexpr dynamic_object overloaded_function::invoke(pointer_view<const dynamic_reference> args) const
{
	for (const function& f : get_overloads())
		if (f.can_invoke(args | PP::transform([](const dynamic_reference& r) -> const type& { return r.get_type(); })))
			return f.invoke_unsafe(PP::begin(args));

	return dynamic_object::create_invalid();
}
