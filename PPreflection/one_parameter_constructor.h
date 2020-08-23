#pragma once
#include "member_like_function.h"

class one_parameter_constructor : public member_like_function
{
public:
	constexpr virtual const type& parameter_type() const noexcept = 0;

	constexpr dynamic_object invoke(const dynamic_reference& arg) const;
};
