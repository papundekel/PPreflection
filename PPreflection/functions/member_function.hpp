#pragma once
#include "PP/ostream.hpp"

#include "member_function.h"

#include "../print_cv.h"
#include "../types/class_type.h"
#include "../types/reference_type.h"

constexpr void PPreflection::member_function::print_name_after_parent(
	PP::ostream& out) const noexcept
{
	print_name_basic(out);

	print_cv(get_cv_qualifier(), out);

	switch (get_ref_qualifier())
	{
		case PP::ref_qualifier::none:
			break;
		case PP::ref_qualifier::lvalue:
			out.write("&");
			break;
		case PP::ref_qualifier::rvalue:
			out.write("&&");
			break;
	}

	print_noexcept(out);

	get_return_type().as_type().print_name_suffix(out);
}
