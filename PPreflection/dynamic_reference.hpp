#pragma once
#include "dynamic_reference.h"

#include "PP/add_pointer.hpp"
#include "PP/add_reference.hpp"
#include "PP/concepts/rvalue_reference.hpp"
#include "PP/overloaded.hpp"
#include "PP/remove_reference.hpp"

#include "types/pointer_type.h"

inline auto PPreflection::dynamic_reference::cast_unsafe(
	PP::concepts::type auto t) const noexcept -> PP_GT(t) &&
{
	return (PP_GT(t) &&)(*reinterpret(PP::add_pointer(!t)));
}

inline auto PPreflection::dynamic_reference::cast(
	PP::concepts::type auto t) const -> PP_GT(t) &&
{
	return cast_unsafe(t);
}

inline auto* PPreflection::dynamic_reference::get_ptr(
	PP::concepts::type auto t) const
{
	return reinterpret(PP::add_pointer(t));
}

inline auto& PPreflection::dynamic_reference::get_ref(
	PP::concepts::type auto t) const&
{
	return cast(t + PP::add_lvalue_tag);
}
inline auto&& PPreflection::dynamic_reference::get_ref(
	PP::concepts::type auto t) const&&
{
	return cast(t + PP::add_rvalue_tag);
}

constexpr PPreflection::dynamic_reference::dynamic_reference(
	auto&& r) noexcept requires
	PP::concepts::different_except_cvref<decltype(r), dynamic_reference> &&
	PP::concepts::different_except_cvref<decltype(r), dynamic_object> &&
	PP::concepts::different_except_cvref<decltype(r), dynamic_variable>

	: dynamic_reference(&r, type::reflect(PP_DECLTYPE(r)))
{}

namespace PPreflection::detail
{
	constexpr auto add_cv_except_to_array(PP::concepts::value auto cv,
	                                      PP::concepts::type auto t) noexcept
	{
		if constexpr (PP::is_array(PP_COPY_TYPE(t)))
			return t;
		else
			return PP::add_cv(cv, t);
	}
}

inline decltype(auto) PPreflection::dynamic_reference::visit(
	PP::concepts::type auto t,
	auto&& f) const
{
	if (is_lvalue)
	{
		switch (referenced_type_cv.cv)
		{
			case PP::cv_qualifier::none:
				return PP_F(f)(
					cast_unsafe(detail::add_cv_except_to_array(
									PP::value<PP::cv_qualifier::none>,
									t) +
				                PP::add_lvalue_tag));
			case PP::cv_qualifier::Const:
				return PP_F(f)(
					cast_unsafe(detail::add_cv_except_to_array(
									PP::value<PP::cv_qualifier::Const>,
									t) +
				                PP::add_lvalue_tag));
			case PP::cv_qualifier::Volatile:
				return PP_F(f)(
					cast_unsafe(detail::add_cv_except_to_array(
									PP::value<PP::cv_qualifier::Volatile>,
									t) +
				                PP::add_lvalue_tag));
			case PP::cv_qualifier::const_volatile:
				return PP_F(f)(
					cast_unsafe(detail::add_cv_except_to_array(
									PP::value<PP::cv_qualifier::const_volatile>,
									t) +
				                PP::add_lvalue_tag));
		}
	}
	else
	{
		switch (referenced_type_cv.cv)
		{
			case PP::cv_qualifier::none:
				return PP_F(f)(cast_unsafe(detail::add_cv_except_to_array(
					PP::value<PP::cv_qualifier::none>,
					t)));
			case PP::cv_qualifier::Const:
				return PP_F(f)(cast_unsafe(detail::add_cv_except_to_array(
					PP::value<PP::cv_qualifier::Const>,
					t)));
			case PP::cv_qualifier::Volatile:
				return PP_F(f)(cast_unsafe(detail::add_cv_except_to_array(
					PP::value<PP::cv_qualifier::Volatile>,
					t)));
			case PP::cv_qualifier::const_volatile:
				return PP_F(f)(cast_unsafe(detail::add_cv_except_to_array(
					PP::value<PP::cv_qualifier::const_volatile>,
					t)));
		}
	}

	return PP_F(f)(cast_unsafe(t));
}

inline decltype(auto) PPreflection::dynamic_reference::visit_ptr(
	PP::concepts::type auto t,
	auto&& f) const
{
	static_assert(PP::is_pointable(PP_COPY_TYPE(t)));

	switch (dynamic_cast<const pointer_type*>(referenced_type_cv.type_ptr)
	            ->remove_pointer()
	            .cv)
	{
		case PP::cv_qualifier::none:
			return PP_F(f)(cast_unsafe(PP::add_pointer(
				PP::add_cv(PP::value<PP::cv_qualifier::none>, t))));
		case PP::cv_qualifier::Const:
			return PP_F(f)(cast_unsafe(PP::add_pointer(
				PP::add_cv(PP::value<PP::cv_qualifier::Const>, t))));
		case PP::cv_qualifier::Volatile:
			return PP_F(f)(cast_unsafe(PP::add_pointer(
				PP::add_cv(PP::value<PP::cv_qualifier::Volatile>, t))));
		case PP::cv_qualifier::const_volatile:
			return PP_F(f)(cast_unsafe(PP::add_pointer(
				PP::add_cv(PP::value<PP::cv_qualifier::const_volatile>, t))));
	}

	return PP_F(f)(cast_unsafe(
		PP::add_pointer(PP::add_cv(PP::value<PP::cv_qualifier::none>, t))));
}

constexpr void* PPreflection::dynamic_reference::get_void_ptr() const
{
	if (is_function)
		return nullptr;
	else
		return ptr_object;
}
