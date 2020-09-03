#pragma once
#include "constructor.h"

class one_parameter_converting_constructor : public constructor
{
protected:
	constexpr virtual void invoke_implementation_one_parameter(void* result, dynamic_reference arg) const noexcept = 0;
	constexpr void invoke_implementation(void* result, const dynamic_reference* args) const noexcept override final
	{
		invoke_implementation_one_parameter(result, args[0]);
	}

public:
	constexpr bool is_explicit() const noexcept override final
	{
		return false;
	}

	constexpr virtual const type& get_parameter_type() const noexcept = 0;

	constexpr dynamic_object invoke(dynamic_reference arg) const;
};
