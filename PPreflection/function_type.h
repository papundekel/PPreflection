#pragma once
#include "type.h"

class Function : public type
{
public:
	constexpr virtual const type& return_type() const noexcept = 0;
	constexpr virtual pointer_view<const cref_t<type>> parameter_types() const noexcept = 0;

	constexpr virtual ref_qualifier get_function_ref_qualifier() const noexcept = 0;
	constexpr virtual cv_qualifier get_function_cv_qualifier() const noexcept = 0;
};
