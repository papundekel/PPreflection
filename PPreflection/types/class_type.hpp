#pragma once
#include "class_type.h"

#include "../descriptor.h"
#include "../functions/constructor.h"

inline PPreflection::dynamic_object PPreflection::class_type::create_instance(PP::any_view<PP::iterator_category::ra, const dynamic_reference&>) const noexcept
{
	return dynamic_object::create_invalid(dynamic_object::invalid_code::no_valid_overload);
}

constexpr void PPreflection::class_type::get_member_function_overloads(PP::string_view name, PP::concepts::iterator auto i_out) const noexcept
{
	return get_descriptors(name, get_member_functions(), i_out);
}

constexpr void PPreflection::class_type::get_static_member_function_overloads(PP::string_view name, PP::concepts::iterator auto i_out) const noexcept
{
	return get_descriptors(name, get_static_member_functions(), i_out);
}

constexpr const PPreflection::user_defined_type* PPreflection::class_type::get_nested_type(PP::string_view name) const noexcept
{
	return get_descriptor(name, get_nested_types());
}

inline PPreflection::dynamic_object PPreflection::class_type::copy_initialize_same_or_derived(dynamic_reference) const noexcept
{
	return dynamic_object::create_invalid(dynamic_object::invalid_code::no_valid_overload);
}
