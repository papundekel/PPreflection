#pragma once
#include "../dynamic_reference.h"
#include "../types/class_type.h"
#include "../types/make_reference_type.h"
#include "../types/reference_type.h"
#include "../types/referencable_type.hpp"
#include "member_function.h"

constexpr void PPreflection::member_function::print_name_after_parent(PP::simple_ostream& out) const noexcept
{
	print_name_basic(out);

	print_cv(get_cv_qualifier(), out);

	switch (get_ref_qualifier())
	{
	case PP::ref_qualifier::none:
		break;
	case PP::ref_qualifier::lvalue:
		out.write("&"); break;
	case PP::ref_qualifier::rvalue:
		out.write("&&"); break;
	}

	print_noexcept(out);
}

inline PPreflection::dynamic_variable PPreflection::member_function::invoke_unsafe(PP::any_iterator<PP::iterator_category::ra, dynamic_reference> arg_iterator, void*) const noexcept
{
	return invoke_unsafe(*arg_iterator, PP::iterator_next(arg_iterator));
}

inline PPreflection::dynamic_variable PPreflection::member_function::invoke(dynamic_reference, PP::any_view<PP::iterator_category::ra, dynamic_reference>) const
{
	return dynamic_variable::create_invalid(dynamic_object::invalid_code::implicit_conversion_error);
}
