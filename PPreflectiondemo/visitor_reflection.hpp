#pragma once
#include "S.hpp"
#include "animals.hpp"

namespace visitors
{
	struct visitor_reflection
	{
		void react_to(const animals::animal& animal);
	};
}
