#pragma once
#include <algorithm>
#include "namespace_t.h"
#include "types/type.h"
#include "descriptor.h"
#include "namespace_function.h"

constexpr const type* namespace_t::get_type(std::string_view name) const noexcept
{
	return get_descriptor(name, get_types());
}

constexpr const overloaded_namespace_function* namespace_t::get_function(std::string_view name) const noexcept
{
	return get_descriptor(name, get_functions());
}
