#pragma once
#include "referencable_type.h"
#include "../any_iterator.h"
#include "../ref_qualifier.h"
#include "../cv_qualifier.h"

class function_type : public referencable_type
{
public:
	constexpr virtual const int& return_type() const noexcept = 0;
	constexpr virtual any_view<const int&> parameter_types() const noexcept = 0;

	constexpr virtual ref_qualifier get_ref_qualifier() const noexcept = 0;
	constexpr virtual cv_qualifier get_cv_qualifier() const noexcept = 0;
};
