#pragma once
#include "dynamic_reference.h"

#include "PP/add_pointer.hpp"
#include "PP/add_reference.hpp"
#include "PP/concepts/rvalue_reference.hpp"
#include "PP/overloaded.hpp"
#include "PP/remove_reference.hpp"

#include "reflect.h"
#include "types/reference_type.h"
#include "types/type.h"

inline auto PPreflection::dynamic_reference::cast_unsafe(PP::concepts::type auto t) const noexcept -> PP_GET_TYPE(t)&&
{
	return (PP_GET_TYPE(t)&&)(*reinterpret(PP::add_pointer(!t)));
}

inline auto PPreflection::dynamic_reference::cast(PP::concepts::type auto t) const -> PP_GET_TYPE(t)&&
{
//	constexpr auto T = PP_COPY_TYPE(t) + PP::add_rvalue_tag;

	//if (type::reflect(T).can_be_initialized(get_type().make_reference(PP::value<!PP::is_rvalue_reference(T)>)))
		return cast_unsafe(t);
//	else
	//	throw bad_cast_exception{};
}

inline auto* PPreflection::dynamic_reference::get_ptr(PP::concepts::type auto t) const
{
	if (type::reflect(t).can_be_pointer_initialized(get_type().remove_reference().type))
		return reinterpret(PP::add_pointer(t));
	else
		return nullptr;
}

inline auto& PPreflection::dynamic_reference::get_ref(PP::concepts::type auto t) const&
{
	return cast(t + PP::add_lvalue_tag);
}
inline auto&& PPreflection::dynamic_reference::get_ref(PP::concepts::type auto t) const&&
{
	return cast(t + PP::add_rvalue_tag);
}

constexpr PPreflection::dynamic_reference::dynamic_reference(auto&& r) noexcept
requires 
	PP::concepts::different_except_cvref<decltype(r), dynamic_reference> &&
	PP::concepts::different_except_cvref<decltype(r), dynamic_object> &&
	PP::concepts::different_except_cvref<decltype(r), dynamic_variable>

	: dynamic_reference(&r, type::reflect(PP_DECLTYPE(r)))
{}

namespace PPreflection::detail
{
	constexpr auto add_cv_except_to_array(PP::concepts::type auto t, PP::concepts::value auto cv) noexcept
	{
		if constexpr (PP::is_array(PP_COPY_TYPE(t)))
			return t;
		else
			return PP::add_cv(cv, t);
	}
}

inline decltype(auto) PPreflection::dynamic_reference::visit(PP::concepts::type auto t, auto&& f) const
{
	if (is_lvalue)
	{
		switch (referenced_type_cv.cv)
		{
		case PP::cv_qualifier::none:
			return PP_FORWARD(f)(cast_unsafe(detail::add_cv_except_to_array(t, PP::value<PP::cv_qualifier::none>) + PP::add_lvalue_tag));
		case PP::cv_qualifier::Const:
			return PP_FORWARD(f)(cast_unsafe(detail::add_cv_except_to_array(t, PP::value<PP::cv_qualifier::Const>) + PP::add_lvalue_tag));
		case PP::cv_qualifier::Volatile:
			return PP_FORWARD(f)(cast_unsafe(detail::add_cv_except_to_array(t, PP::value<PP::cv_qualifier::Volatile>) + PP::add_lvalue_tag));
		case PP::cv_qualifier::const_volatile:
			return PP_FORWARD(f)(cast_unsafe(detail::add_cv_except_to_array(t, PP::value<PP::cv_qualifier::const_volatile>) + PP::add_lvalue_tag));
		}
	}
	else
	{
		switch (referenced_type_cv.cv)
		{
		case PP::cv_qualifier::none:
			return PP_FORWARD(f)(cast_unsafe(detail::add_cv_except_to_array(t, PP::value<PP::cv_qualifier::none>)));
		case PP::cv_qualifier::Const:
			return PP_FORWARD(f)(cast_unsafe(detail::add_cv_except_to_array(t, PP::value<PP::cv_qualifier::Const>)));
		case PP::cv_qualifier::Volatile:
			return PP_FORWARD(f)(cast_unsafe(detail::add_cv_except_to_array(t, PP::value<PP::cv_qualifier::Volatile>)));
		case PP::cv_qualifier::const_volatile:
			return PP_FORWARD(f)(cast_unsafe(detail::add_cv_except_to_array(t, PP::value<PP::cv_qualifier::const_volatile>)));
		}
	}

	return PP_FORWARD(f)(cast_unsafe(t));
}

constexpr void* PPreflection::dynamic_reference::get_void_ptr() const
{
	return std::visit(PP::overloaded([]
		(void* p)
		{
			return p;
		}, []
		(void(*)()) -> void*
		{
			return nullptr;
		}), ptr);
}
