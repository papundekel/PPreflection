#include "null_type.h"

#include "../reflect_dummy.hpp"

PPreflection::dynamic_object PPreflection::null_type::create_instance() const noexcept
{
	return dynamic_object::create(PP::type<decltype(nullptr)>);
}
