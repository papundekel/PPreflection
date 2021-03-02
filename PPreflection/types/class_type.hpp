#pragma once
#include "class_type.h"

#include "../descriptor.h"
#include "../functions/constructor.h"

inline PPreflection::dynamic_variable PPreflection::class_type::create_instance(PP::any_view<PP::iterator_category::ra, const dynamic_reference&> args) const noexcept
{
	return get_constructors().invoke(args);
}
constexpr const PPreflection::overloaded_member_function* PPreflection::class_type::get_member_function(PP::string_view name) const noexcept
{
	return get_descriptor(name, get_member_functions());
}
constexpr const PPreflection::overloaded_static_member_function* PPreflection::class_type::get_static_member_function(PP::string_view name) const noexcept
{
	return get_descriptor(name, get_static_member_functions());
}
constexpr const PPreflection::user_defined_type* PPreflection::class_type::get_nested_class(PP::string_view name) const noexcept
{
	return get_descriptor(name, get_nested_classes());
}
