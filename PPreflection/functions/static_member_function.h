#pragma once
#include "../named_descriptor.h"
#include "maybe_static_member_function.h"

namespace PPreflection
{
///
/// @brief Represents a static member function.
///
class static_member_function : public maybe_static_member_function
{};
}
