#include "null_type.hpp"

#include "../reflect_dummy.hpp"

PPreflection::dynamic_object PPreflection::null_type::create_instance() const noexcept
{
	return dynamic_object::create(PP::type<decltype(nullptr)>);
}
