#include "dynamic_variable.h"

#include "descriptor.hpp"
#include "dynamic_object.hpp"
#include "functions/function.hpp"
#include "functions/member_function.hpp"
#include "overload_resolution.hpp"
#include "parent_descriptor_reference.hpp"
#include "parent_descriptor_reference_strong.hpp"
#include "types/class_type.hpp"
#include "types/cv_type.hpp"
#include "types/known_bound_array_type.hpp"
#include "types/non_array_object_type.hpp"
#include "types/non_user_defined_type.hpp"
#include "types/pointer_to_member_type.hpp"
#include "types/reference_type.hpp"
#include "types/unknown_bound_array_type.hpp"

PPreflection::dynamic_variable PPreflection::dynamic_variable::create_invalid(dynamic_object::invalid_code code) noexcept
{
	return dynamic_variable(dynamic_object::create_invalid(code));
}

PPreflection::dynamic_variable PPreflection::dynamic_variable::create_void() noexcept
{
	return dynamic_variable(dynamic_object::create_void());
}
