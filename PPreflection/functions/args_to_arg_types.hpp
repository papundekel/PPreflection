#pragma once
#include "../PPany_view.hpp"
#include "../dynamic_reference.h"
#include "../types/reference_type.h"
#include "function.h"

namespace PPreflection
{
	constexpr PP::any_view<PP::iterator_category::ra, const reference_type&> args_to_arg_types(PP::any_view<PP::iterator_category::ra, const dynamic_reference&> args)
	{
		return args | PP::transform([](const dynamic_reference& r) -> const reference_type& { return r.get_type(); });
	}
}
