#pragma once
#include "namespace_function.h"
#include "overloaded_namespace_function.h"

constexpr const namespace_t& namespace_function::get_parent() const noexcept
{
	return get_overloaded_function().get_parent();
}
