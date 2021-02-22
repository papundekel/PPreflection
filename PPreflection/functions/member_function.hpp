#pragma once
#include "function.h"
#include "member_function.h"
#include "../dynamic_reference.h"
#include "../types/class_type.h"
#include "../types/reference_type.h"

constexpr void PPreflection::member_function::print_name_after_parent(PP::simple_ostream& out) const noexcept
{
	print_name_basic(out);

	switch (get_cv_qualifier())
	{
	case PP::cv_qualifier::Const:
		out.write(" const"); break;
	case PP::cv_qualifier::Volatile: break;
		out.write(" volatile"); break;
	case PP::cv_qualifier::const_volatile:
		out.write(" const volatile"); break;
	}

	switch (get_ref_qualifier())
	{
	case PP::ref_qualifier::lvalue:
		out.write("&"); break;
	case PP::ref_qualifier::rvalue:
		out.write("&&"); break;
	}

	print_noexcept(out);
}
constexpr bool PPreflection::member_function::has_name(PP::string_view name) const noexcept
{
	// TODO
	return false;
}

constexpr bool PPreflection::member_function::can_invoke(const reference_type& caller_arg_type) const noexcept
{
	const referencable_type& caller_par_type = get_parent();

	switch (get_ref_qualifier())
	{
	//case PP::ref_qualifier::none:
	case PP::ref_qualifier::lvalue:
		return caller_par_type.make_reference(PP::value_false).can_be_initialized(caller_arg_type);
	case PP::ref_qualifier::rvalue:
		return caller_par_type.make_reference(PP::value_true).can_be_initialized(caller_arg_type);
	default:
		return caller_par_type.make_reference(PP::value_false).can_be_initialized(caller_arg_type) || caller_par_type.make_reference(PP::value_true).can_be_initialized(caller_arg_type);
	}
}

inline PPreflection::dynamic_variable PPreflection::member_function::invoke_unsafe(PP::any_iterator<PP::iterator_category::ra, const dynamic_reference&> arg_iterator) const noexcept
{
	return invoke_unsafe_member(*arg_iterator, arg_iterator + 1);
}

constexpr bool PPreflection::member_function::can_invoke(PP::any_view<PP::iterator_category::ra, const reference_type&> argument_types) const noexcept
{
	return
		!PP::view_empty(argument_types) &&
		can_invoke(argument_types.begin()[0]) &&
		function::can_invoke(1_s >> argument_types);
}

inline PPreflection::dynamic_variable PPreflection::member_function::invoke(dynamic_reference caller, PP::any_view<PP::iterator_category::ra, const dynamic_reference&> args) const
{
	if (can_invoke(caller.get_type()) && function::can_invoke(args | PP::transform([](const dynamic_reference& r) -> const reference_type& { return r.get_type(); })))
		return invoke_unsafe_member(caller, PP::view_begin(args));
	else
		return dynamic_variable::create_invalid(dynamic_object::invalid_code::implicit_conversion_error);
}

inline PPreflection::dynamic_variable PPreflection::overloaded_member_function::invoke(dynamic_reference caller, PP::any_view<PP::iterator_category::ra, const dynamic_reference&> args) const
{
	for (const member_function& f : get_overloads())
		if (f.can_invoke(caller.get_type()) && f.function::can_invoke(args | PP::transform([](const dynamic_reference& r) -> const reference_type& { return r.get_type(); })))
			return f.invoke_unsafe_member(caller, PP::view_begin(args));

	return dynamic_variable::create_invalid(dynamic_object::invalid_code::implicit_conversion_error);
}
