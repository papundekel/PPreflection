#pragma once
#include "PP/cv_qualifier.hpp"
#include "PP/ostream.hpp"

namespace PPreflection
{
	constexpr void print_cv(PP::cv_qualifier cv, PP::ostream& out)
	{
		if (PP::cv_is_const(cv))
			out.write(" const");
		if (PP::cv_is_volatile(cv))
			out.write(" volatile");
	}
}
