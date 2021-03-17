#pragma once
#include "class_type.h"

#include "../descriptor.h"
#include "../functions/constructor.h"

inline PPreflection::dynamic_variable PPreflection::class_type::create_instance(PP::any_view<PP::iterator_category::ra, const dynamic_reference&> args) const noexcept
{
	for (const constructor& c : get_constructors())
		if (c.can_invoke(function::args_to_types_transform(args)))
			return c.invoke(args);

	return dynamic_variable::create_invalid(dynamic_object::invalid_code::no_valid_overload);
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
