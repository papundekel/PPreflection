#pragma once
#include "referencable_type.h"
#include "../PP/PP/any_iterator.hpp"
#include "../PP/PP/ref_qualifier.hpp"
#include "../PP/PP/cv_qualifier.hpp"

class function_type : public referencable_type
{
public:
	constexpr virtual const int& return_type() const noexcept = 0;
	constexpr virtual PP::any_view<const int&> parameter_types() const noexcept = 0;

	constexpr virtual PP::ref_qualifier get_ref_qualifier() const noexcept = 0;
	constexpr virtual PP::cv_qualifier get_cv_qualifier() const noexcept = 0;
};
