#pragma once
#include "Namespace.h"

#include "PP/push_back_iterator.hpp"
#include "PP/simple_vector.hpp"
#include "PP/view_remove.hpp"

#include "args_to_types.hpp"
#include "descriptor.h"
#include "functions/functions.h"
#include "overload_resolution.hpp"
#include "parent_descriptor_reference.h"
#include "types/types.h"

constexpr PPreflection::parent_descriptor_reference PPreflection::Namespace::get_parent(void*) const noexcept
{
	if (const auto& parent = get_parent(); &parent != this)
		return parent;
	else
		return {};
}

constexpr const PPreflection::Namespace* PPreflection::Namespace::get_namespace(PP::string_view name) const noexcept
{
	return get_descriptor(name, get_namespaces());
}
constexpr const PPreflection::user_defined_type* PPreflection::Namespace::get_type(PP::string_view name) const noexcept
{
	return get_descriptor(name, get_types());
}
constexpr void PPreflection::Namespace::get_function_overloads(PP::string_view name, PP::concepts::iterator auto i_out) const noexcept
{
	get_descriptors(name, get_functions(), i_out);
}

PPreflection::dynamic_variable PPreflection::Namespace::invoke(PP::string_view, PP::any_view<PP::iterator_category::ra, dynamic_reference>) const noexcept
{
	return dynamic_variable::create_invalid(dynamic_object::invalid_code::no_valid_overload);
}
PPreflection::dynamic_variable PPreflection::Namespace::invoke_qualified(PP::string_view function_name, PP::any_view<PP::iterator_category::ra, dynamic_reference> args) const noexcept
{
	PP::simple_vector<PP::reference_wrapper<const namespace_function&>> candidate_functions;
	get_function_overloads(function_name, PP::push_back_iterator(candidate_functions));

	PP::simple_vector<dynamic_reference_type> arg_types;
	
	for (auto r : args)
		arg_types.push_back(r.get_type());

	auto [f, error_code] = overload_resolution(candidate_functions, arg_types, PP::empty_view<standard_conversion_sequence>{}, true);
	if (f)
		return f->invoke(args);
	else
		return dynamic_variable::create_invalid(dynamic_object::invalid_code::overload_resolution_error);
}
