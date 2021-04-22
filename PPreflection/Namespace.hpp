#pragma once
#include "Namespace.h"

#include "PP/push_back_iterator.hpp"
#include "PP/ref_wrap.hpp"
#include "PP/small_optimized_vector.hpp"
#include "PP/view_remove.hpp"

#include "candidate_functions.hpp"
#include "dynamic_variable.h"
#include "functions/namespace_function.h"

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

PPreflection::dynamic_variable PPreflection::Namespace::invoke(PP::string_view, PP::any_view<PP::iterator_category::ra, dynamic_reference>) const
{
	return dynamic_variable::create_invalid(dynamic_object::invalid_code::no_valid_overload);
}

PPreflection::dynamic_variable PPreflection::Namespace::invoke_qualified(PP::string_view function_name, PP::any_view<PP::iterator_category::ra, dynamic_reference> args) const
{
	return candidate_functions(get_functions()).trim_name(function_name).invoke(PP::move(args));
}
