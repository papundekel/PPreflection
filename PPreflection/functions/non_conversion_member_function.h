#pragma once
#include "member_function.h"
#include "named_function.h"

namespace PPreflection
{
///
/// @brief Represents a non-conversion member function.
///
class non_conversion_member_function
	: public detail::named_function<member_function>
{};
}
