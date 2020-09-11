#pragma once
#include "non_member_function_type.h"
#include "ref_qualifier.hpp"
#include "cv_qualifier.hpp"

class function_type : public non_member_function_type
{
public:
	constexpr virtual PP::cv_qualifier get_cv_qualifier() const noexcept = 0;
	constexpr virtual PP::ref_qualifier get_ref_qualifier() const noexcept = 0;
};
