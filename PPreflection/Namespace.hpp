#pragma once
#include "Namespace.h"

#include "PP/push_back_iterator.hpp"
#include "PP/simple_vector.hpp"
#include "PP/view_remove.hpp"

#include "descriptor.h"
#include "functions/functions.h"
#include "parent_descriptor_reference.h"
#include "types/types.h"

constexpr PPreflection::parent_descriptor_reference PPreflection::Namespace::get_parent(void*) const noexcept
{
	return get_parent();
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

PPreflection::dynamic_variable PPreflection::Namespace::invoke(PP::string_view, PP::any_view<PP::iterator_category::ra, const dynamic_reference&>) const noexcept
{
	return dynamic_variable::create_invalid(dynamic_object::invalid_code::no_valid_overload);
}
PPreflection::dynamic_variable PPreflection::Namespace::invoke_qualified(PP::string_view function_name, PP::any_view<PP::iterator_category::ra, const dynamic_reference&> args) const noexcept
{
	PP::simple_vector<PP::reference_wrapper<const namespace_function&>> candidate_functions;
	get_function_overloads(function_name, PP::push_back_iterator(candidate_functions));

	candidate_functions.erase_until_end(PP::view_remove([c = PP::view_count(args)]
		(const function& nf)
		{
			return PP::view_count(nf.parameter_types()) != c;
		}, candidate_functions));

	auto& viable_functions = candidate_functions;

	if (!PP::view_empty(viable_functions))
	{
		const function& first = viable_functions[0];
		return first.invoke(args);
	}
	else
		return dynamic_variable::create_invalid(dynamic_object::invalid_code::no_valid_overload);
}
