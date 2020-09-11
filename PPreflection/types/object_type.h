#pragma once
#include "referencable_type.h"
#include "../../PP/PP/cv_qualifier.hpp"

class object_type : public referencable_type
{
public:
	constexpr virtual PP::cv_qualifier get_cv_qualifier() const noexcept = 0;
};
