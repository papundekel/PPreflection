#pragma once
#include "type.h"

class referencable_type;

class reference_type : public type
{
public:
	constexpr virtual const referencable_type& remove_reference() const noexcept = 0;

	constexpr virtual bool is_lvalue() const noexcept = 0;

	template <bool rvalue>
	constexpr const reference_type& make_reference() const noexcept;

	constexpr type_disjunction_reference<reference_type, pointable_type> reference_or_pointable() const noexcept override final
	{
		return *this;
	}

	constexpr bool can_be_initialized(const reference_type& initializer) const noexcept
	{
		return true;
	}
};
