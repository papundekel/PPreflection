#pragma once
#include "PP/view.hpp"

namespace PPreflector
{
	constexpr void for_each_with_delimiters(auto&& f,
											auto&& delimiter_f,
											PP::concepts::view auto&& view)
	{
		auto [i, end] = PP::view_begin_end(PP_FORWARD(view));

		if (i != end)
		{
			PP_FORWARD(f)(*i);
			++i;

			for (; i != end; ++i)
			{
				PP_FORWARD(delimiter_f)();
				PP_FORWARD(f)(*i);
			}
		}
	}
}
