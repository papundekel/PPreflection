#pragma once
#include "descriptor.h"
#include "Namespace.h"
#include "types/types.h"
#include "functions/functions.h"

constexpr const PPreflection::Namespace* PPreflection::Namespace::get_namespace(PP::string_view name) const noexcept
{
	return get_descriptor(name, get_namespaces());
}
constexpr const PPreflection::user_defined_type* PPreflection::Namespace::get_type(PP::string_view name) const noexcept
{
	return get_descriptor(name, get_types());
}
constexpr const PPreflection::overloaded_namespace_function* PPreflection::Namespace::get_function(PP::string_view name) const noexcept
{
	return get_descriptor(name, get_functions());
}
