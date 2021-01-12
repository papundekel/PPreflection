#pragma once
#include "referencable_type.h"
#include "dynamic_reference_type.h"
#include "dynamic_lvalue_reference_type.h"
#include "dynamic_rvalue_reference_type.h"

constexpr dynamic_lvalue_reference_type referencable_type::make_lreference() const noexcept
{
	return dynamic_lvalue_reference_type(*this);
}
constexpr dynamic_rvalue_reference_type referencable_type::make_rreference() const noexcept
{
	return dynamic_rvalue_reference_type(*this);
}

template <bool rvalue>
constexpr auto referencable_type::make_reference() const noexcept
{
	if constexpr (rvalue)
		return make_rreference();
	else
		return make_lreference();
}
constexpr dynamic_reference_type referencable_type::make_reference(bool lvalue) const noexcept
{
	return dynamic_reference_type(*this, lvalue);
}
