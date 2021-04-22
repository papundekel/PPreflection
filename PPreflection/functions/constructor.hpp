#pragma once
#include "constructor.h"

#include "../dynamic_variable.h"

PPreflection::dynamic_variable PPreflection::constructor::invoke_unsafe(PP::any_iterator<PP::iterator_category::ra, dynamic_reference> arg_iterator, void*) const
{
	return dynamic_variable(invoke_unsafe(PP::move(arg_iterator)));
}

PPreflection::dynamic_object PPreflection::constructor::invoke(PP::any_view<PP::iterator_category::ra, dynamic_reference>) const
{
	return dynamic_object::create_invalid(dynamic_object::invalid_code::implicit_conversion_error);
}
