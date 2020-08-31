#pragma once
#include <type_traits>
#include <algorithm>
#include "type.h"
#include "reflect.h"
#include "descriptor.h"
#include "map_pack.h"
#include "get_value.h"
#include "function.h"
#include "../Papo/PP/any_of.hpp"

constexpr cv_qualifier type::get_cv_qualifier() const noexcept
{
	if (is_const() && is_volatile())
		return cv_qualifier::const_volatile;
	else if (is_const() && !is_volatile())
		return cv_qualifier::const_;
	else if (is_volatile())
		return cv_qualifier::volatile_;
	else
		return cv_qualifier::none;
}
constexpr void type::print_name(simple_ostream& out) const noexcept
{
	print_name_first(out);
	print_name_second(out);
}

constexpr bool type::is_pointer_like() const noexcept
{
	return get_ref_qualifier() != ref_qualifier::none;
}

constexpr bool type::is_derived_from(const type& base) const noexcept
{
	if (!is_pointer_like() && *this == base)
		return true;

	return PP::any_of(get_direct_bases(),
		[&base](const type& direct_base)
		{
			return direct_base.is_derived_from(base);
		});
}
constexpr bool type::is_reference() const noexcept
{
	return get_ref_qualifier() != ref_qualifier::none;
}

constexpr bool type::can_pointer_like_initialize_inner(const type& other) const noexcept
{
	return
		cv_at_most(other)
		&&
		remove_cv().is_derived_from(other.remove_cv());
}

constexpr bool type::can_reference_initialize_no_user_conversion(const type& ref_type) const noexcept
{
	return
	(
		(
			// X& = Y&
			get_ref_qualifier() == ref_qualifier::lvalue &&
			ref_type.get_ref_qualifier() == ref_qualifier::lvalue
		)
		||
		(
			// ... = Y&&
			get_ref_qualifier() == ref_qualifier::rvalue
			&&
			(
				// X&& = Y&&
				ref_type.get_ref_qualifier() == ref_qualifier::rvalue
				||
				// const X& = Y&&
				(
					ref_type.get_ref_qualifier() == ref_qualifier::lvalue
					&&
					ref_type.remove_reference().get_cv_qualifier() == cv_qualifier::const_
				)
			)
		)
	)
	&&
	// x Br = y Dr where x >= y and B is base of D
	remove_reference().can_pointer_like_initialize_inner(ref_type.remove_reference());
}
constexpr bool type::can_reference_initialize(const type& ref_type) const noexcept
{
	return can_reference_initialize_no_user_conversion(ref_type);
}

constexpr bool type::can_initialize(const type& parameter_type) const noexcept
{
	if (parameter_type.is_reference())
		return can_reference_initialize(parameter_type);
	else
		return false;
}

constexpr bool type::L1(const type& par_type) const noexcept
{
	return
		get_ref_qualifier() == ref_qualifier::lvalue
		&&
		remove_reference().can_pointer_like_initialize_inner(par_type.remove_reference());
}

constexpr const conversion_function* type::L2(const type& par_type) const noexcept
{
	//TODO
	return nullptr;
}

constexpr bool operator==(const type& a, const type& b) noexcept
{
	if (a.get_category() == b.get_category())
	{
		switch (a.get_category())
		{
		case type::compound_category::basic:
			return
				a.get_cv_qualifier() == b.get_cv_qualifier() &&
				a.get_id() == b.get_id();
		case type::compound_category::reference:
			return
				a.get_ref_qualifier() == b.get_ref_qualifier() &&
				a.remove_reference() == b.remove_reference();
		case type::compound_category::pointer:
			return
				a.get_cv_qualifier() == b.get_cv_qualifier() &&
				a.remove_pointer() == b.remove_pointer();
		case type::compound_category::pointer_to_member:
			return
				a.get_cv_qualifier() == b.get_cv_qualifier() &&
				a.member_pointer_class() == b.member_pointer_class() &&
				a.member_pointer_type() == b.member_pointer_type();
		case type::compound_category::array:
			return
				a.get_extent() == b.get_extent() &&
				a.remove_extent() == b.remove_extent();
		case type::compound_category::function:
			return
				a.return_type() == b.return_type() &&
				a.get_function_cv_qualifier() == b.get_function_cv_qualifier() &&
				a.get_function_ref_qualifier() == b.get_function_ref_qualifier() &&
				std::equal(a.parameter_types().begin(), a.parameter_types().end(), b.parameter_types().begin(), b.parameter_types().end());
		}
	}

	return false;
}

constexpr bool type::cv_at_most(const type& other) const noexcept
{
	return (!is_const() || other.is_const()) && (!is_volatile() || other.is_volatile());
}

template <bool rvalue>
constexpr const type& type::add_reference() const noexcept
{
	if constexpr (rvalue)
		return add_rreference();
	else
		return add_lreference();
}

template <bool rvalue>
constexpr const type& type::make_reference() const noexcept
{
	return remove_reference().add_reference<rvalue>();
}

constexpr const overloaded_member_function* type::get_member_function(std::string_view name) const noexcept
{
	return descriptor::get_descriptor(name, get_member_functions());
}

constexpr dynamic_object type::create_instance(pointer_view<const dynamic_reference> args) const
{
	if (auto* ctrs = get_constructors(); ctrs)
		return ctrs->invoke(args);
	else
		throw 0;
}
