#include "dynamic_variable.hpp"

#include "descriptor.hpp"
#include "dynamic_reference.hpp"
#include "functions/functions.hpp"
#include "overload_resolution.hpp"
#include "parent_descriptor_reference.hpp"
#include "parent_descriptor_reference_strong.hpp"
#include "types/types.hpp"

PPreflection::dynamic_variable PPreflection::dynamic_variable::create_invalid(dynamic_object::invalid_code code) noexcept
{
	return dynamic_variable(dynamic_object::create_invalid(code));
}

PPreflection::dynamic_variable PPreflection::dynamic_variable::create_void() noexcept
{
	return dynamic_variable(dynamic_object::create_void());
}
