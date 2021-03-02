#pragma once
#include "referencable_type.h"

#include "dynamic_lvalue_reference_type.h"
#include "dynamic_reference_type.h"
#include "dynamic_rvalue_reference_type.h"

constexpr PPreflection::dynamic_lvalue_reference_type PPreflection::referencable_type::make_lreference() const noexcept
{
	return dynamic_lvalue_reference_type(*this);
}
constexpr PPreflection::dynamic_rvalue_reference_type PPreflection::referencable_type::make_rreference() const noexcept
{
	return dynamic_rvalue_reference_type(*this);
}

constexpr auto PPreflection::referencable_type::make_reference(PP::concepts::value auto rvalue) const noexcept
{
	if constexpr (PP_GET_VALUE(rvalue))
		return make_rreference();
	else
		return make_lreference();
}
constexpr PPreflection::dynamic_reference_type PPreflection::referencable_type::make_reference(bool lvalue) const noexcept
{
	return dynamic_reference_type(*this, lvalue);
}
