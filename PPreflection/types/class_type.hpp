#pragma once
#include "class_type.h"

#include "../conversion_sequence.h"
#include "../initialization.h"
#include "non_union_class_type.h"

constexpr void PPreflection::class_type::get_member_functions(
	PP::string_view name,
	PP::concepts::iterator auto i_out) const noexcept
{
	return get_descriptors(name, get_member_functions(), i_out);
}

constexpr void PPreflection::class_type::get_static_member_functions(
	PP::string_view name,
	PP::concepts::iterator auto i_out) const noexcept
{
	return get_descriptors(name, get_static_member_functions(), i_out);
}

constexpr const PPreflection::user_defined_type*
PPreflection::class_type::get_nested_type(PP::string_view name) const noexcept
{
	return get_descriptor(name, get_nested_types());
}

inline PPreflection::dynamic_object
	PPreflection::class_type::copy_initialize_same_or_derived(
		dynamic_reference) const noexcept
{
	return dynamic_object::create_invalid(
		dynamic_object::invalid_code::no_valid_overload);
}

constexpr void PPreflection::class_type::get_conversion_functions_inherited(
	PP::concepts::iterator auto i_out) const noexcept
{
	for (const auto& cf : get_conversion_functions())
		*i_out++ = cf;

	if (const auto* non_union_this_ptr = as_non_union_class())
		for (const auto& bc : non_union_this_ptr->get_base_classes())
			bc.get_conversion_functions_inherited(i_out);
}

constexpr PPreflection::detail::standard_conversion_sequence
PPreflection::class_type::make_standard_conversion_sequence_impl(
	const non_array_object_type&) const noexcept
{
	return detail::standard_conversion_sequence::create_invalid();
}
