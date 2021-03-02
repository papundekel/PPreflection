#include "dynamic_variable.hpp"

PPreflection::dynamic_variable PPreflection::dynamic_variable::create_invalid(dynamic_object::invalid_code code) noexcept
{
	return dynamic_variable(dynamic_object::create_invalid(code));
}
