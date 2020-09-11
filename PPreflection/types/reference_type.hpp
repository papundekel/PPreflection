#pragma once
#include "reference_type.h"
#include "referencable_type.h"

template <bool rvalue>
constexpr const reference_type& reference_type::make_reference() const noexcept
{
	remove_reference().make_reference<rvalue>();
}
