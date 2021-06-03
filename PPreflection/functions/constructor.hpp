#pragma once
#include "constructor.h"

#include "../dynamic_variable.h"

PPreflection::dynamic_variable PPreflection::constructor::invoke_unsafe(
	PP::any_iterator<PP::iterator_category::ra, dynamic_reference> arg_iterator,
	void*) const
{
	return dynamic_variable(invoke_unsafe(PP::move(arg_iterator)));
}
