#pragma once
#include "referencable_type.h"
#include "../../PP/PP/cv_qualifier.hpp"

class reference_type;

class object_type : public referencable_type
{
public:
	constexpr virtual const reference_type& add_lreference() const noexcept = 0;
	constexpr virtual const reference_type& add_rreference() const noexcept = 0;

	constexpr virtual PP::cv_qualifier get_cv_qualifier() const noexcept = 0;
};
