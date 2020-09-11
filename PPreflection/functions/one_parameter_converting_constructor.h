#pragma once
#include "constructor.h"

class one_parameter_converting_constructor : public constructor
{
protected:
	inline virtual dynamic_variable invoke_unsafe_one_parameter(dynamic_reference arg) const noexcept = 0;
	inline dynamic_variable invoke_unsafe(PP::any_iterator<const dynamic_reference&> arg_iterator) const noexcept override final
	{
		return invoke_unsafe_one_parameter(arg_iterator[0]);
	}

public:
	constexpr bool is_explicit() const noexcept override final
	{
		return false;
	}

	constexpr virtual const type& get_parameter_type() const noexcept = 0;

	inline dynamic_variable invoke(dynamic_reference arg) const;
};
