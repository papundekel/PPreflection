#pragma once
#include "pointable_type.h"
#include "../../PP/PP/cv_qualifier.hpp"

class void_type : public pointable_type
{
public:
	constexpr virtual PP::cv_qualifier get_cv_qualifier() const noexcept = 0;
};
