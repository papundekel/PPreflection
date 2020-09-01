#pragma once
#include "overloaded_member_function.h"
#include "member_function.h"
#include "pointer_view.hpp"

constexpr dynamic_object overloaded_member_function::invoke(dynamic_reference caller, pointer_view<const dynamic_reference> args) const
{
	for (const member_function& f : get_overloads())
		if (f.can_invoke(caller) && f.function::can_invoke(args))
			return f.invoke_unsafe(caller, args);

	// weird workaround, compiler won't allow a throw expression in a constexpr function
	return [](bool x)
	{
		if (x)
			throw 0;
		else
			return dynamic_object{};
	}(true);
}
