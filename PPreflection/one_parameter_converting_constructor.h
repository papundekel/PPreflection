#pragma once
#include "constructor.h"

class one_parameter_converting_constructor : public constructor
{
protected:
	constexpr virtual dynamic_object invoke_unsafe_one_parameter(dynamic_reference arg) const noexcept = 0;
	constexpr dynamic_object invoke_unsafe(any_iterator<const dynamic_reference&> arg_iterator) const noexcept override final
	{
		return invoke_unsafe_one_parameter(arg_iterator[0]);
	}

public:
	constexpr bool is_explicit() const noexcept override final
	{
		return false;
	}

	constexpr virtual const type& get_parameter_type() const noexcept = 0;

	constexpr dynamic_object invoke(dynamic_reference arg) const;
};
