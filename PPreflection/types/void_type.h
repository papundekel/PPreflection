#pragma once
#include "pointable_type.h"
#include "../cv_qualifier.h"

class void_type : public pointable_type
{
public:
	constexpr virtual cv_qualifier get_cv_qualifier() const noexcept = 0;
};
