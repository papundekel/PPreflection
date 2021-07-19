#pragma once
#include "PP/view.hpp"

namespace PPreflector
{
	constexpr void for_each_with_delimiters(auto&& f,
	                                        auto&& delimiter_f,
	                                        PP::concepts::view auto&& view)
	{
		auto [i, end] = PP::view_begin_end(PP_F(view));

		if (i != end)
		{
			PP_F(f)(*i);
			++i;

			for (; i != end; ++i)
			{
				PP_F(delimiter_f)();
				PP_F(f)(*i);
			}
		}
	}
}
