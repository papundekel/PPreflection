#pragma once
#include "pointable_type.h"

class reference_type;

class referencable_type : public pointable_type
{
	constexpr virtual const reference_type& make_lreference() const noexcept = 0;
	constexpr virtual const reference_type& make_rreference() const noexcept = 0;

public:
	template <bool rvalue>
	constexpr const reference_type& make_reference() const noexcept
	{
		if constexpr (rvalue)
			return make_rreference();
		else
			return make_lreference();
	}
};
