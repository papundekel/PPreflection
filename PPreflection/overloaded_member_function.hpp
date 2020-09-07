#pragma once
#include "overloaded_member_function.h"
#include "member_function.h"

constexpr dynamic_object overloaded_member_function::invoke(dynamic_reference caller, pointer_view<const dynamic_reference> args) const
{
	for (const member_function& f : get_overloads())
		if (f.can_invoke(caller.get_type()) && f.function::can_invoke(args | PP::transform([](const dynamic_reference& r) -> const type& { return r.get_type(); })))
			return f.invoke_unsafe_member(caller, PP::begin(args));

	return dynamic_object::create_invalid();
}
