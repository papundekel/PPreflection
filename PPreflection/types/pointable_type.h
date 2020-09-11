#pragma once
#include "type.h"

class pointer_type;

class pointable_type : public type
{
public:
	constexpr virtual const pointer_type& make_pointer() const noexcept = 0;

	constexpr type_disjunction_reference<reference_type, pointable_type> reference_or_pointable() const noexcept override final
	{
		return *this;
	}

	constexpr bool can_be_pointer_initialized(const pointable_type& initializer) const noexcept
	{
		return true;
	}
};
