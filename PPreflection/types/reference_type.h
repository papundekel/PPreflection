#pragma once
#include "type.h"

class referencable_type;

class reference_type : public type
{
public:
	virtual const referencable_type& remove_reference() const noexcept = 0;

	virtual bool is_lvalue() const noexcept = 0;

	template <bool rvalue>
	const reference_type& make_reference() const noexcept;

	type_disjunction_reference<reference_type, pointable_type> reference_or_pointable() const noexcept override final
	{
		return *this;
	}
};
