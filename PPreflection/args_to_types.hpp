#pragma once
#include "PP/transform_view.hpp"
#include "PP/view.hpp"

#include "dynamic_reference.h"

namespace PPreflection
{
	constexpr auto args_to_types(PP::concepts::view auto&& args) noexcept
	{
		return PP_FORWARD(args) | PP::transform(
									  [](dynamic_reference r)
									  {
										  return r.get_type();
									  });
	}
}
