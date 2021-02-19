#pragma once
#include "add_pointer.hpp"
#include "add_reference.hpp"
#include "concepts/rvalue_reference.hpp"
#include "dynamic_reference.h"
#include "overloaded.hpp"
#include "reflect.h"
#include "reinterpret_cast.hpp"
#include "remove_reference.hpp"
#include "types/reference_type.h"
#include "types/type.h"

constexpr PPreflection::dynamic_reference::dynamic_reference(const void* ptr, const reference_type& t) noexcept
	: ptr(const_cast<void*>(ptr))
	, type_(t)
{}

constexpr auto PPreflection::dynamic_reference::cast_unsafe(PP::concepts::type auto t) const noexcept -> PP_GET_TYPE(t)&&
{
	return (PP_GET_TYPE(t)&&)(*PP::reinterpret__cast(!PP::add_pointer(t), ptr));
}

constexpr auto PPreflection::dynamic_reference::cast(PP::concepts::type auto t) const -> PP_GET_TYPE(t)&&
{
	constexpr auto T = PP_COPY_TYPE(t) + PP::add_rvalue_tag;

	if (type::reflect(T).can_be_initialized(type_.make_reference(PP::value<!PP::is_rvalue_reference(T)>)))
		return cast_unsafe(t);
	else
		throw bad_cast_exception{};
}

auto* PPreflection::dynamic_reference::get_ptr(PP::concepts::type auto t) const
{
	if (type::reflect(t).can_be_pointer_initialized(type_.remove_reference()))
		return PP::reinterpret__cast(PP::add_pointer(t), ptr);
	else
		return nullptr;
}

auto& PPreflection::dynamic_reference::get_ref(PP::concepts::type auto t) const&
{
	return cast(t + PP::add_lvalue_tag);
}
auto&& PPreflection::dynamic_reference::get_ref(PP::concepts::type auto t) const&&
{
	return cast(t + PP::add_rvalue_tag);
}

constexpr PPreflection::dynamic_reference::dynamic_reference(auto&& r) noexcept
requires ((
	!PP::is_same_except_cvref* PP::type<dynamic_reference> &&
	!PP::is_same_except_cvref* PP::type<dynamic_object> &&
	!PP::is_same_except_cvref* PP::type<dynamic_variable>)(PP_DECLTYPE(r)))

	: dynamic_reference(&r, type::reflect(PP_DECLTYPE(r)))
{}
