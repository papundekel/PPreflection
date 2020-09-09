#pragma once
#include "referencable_type.h"
#include "../cv_qualifier.h"

class reference_type;

class object_type : public referencable_type
{
	cv_qualifier cv;

public:
	explicit constexpr object_type(cv_qualifier cv)
		: cv(cv)
	{}

	constexpr virtual const reference_type& add_lreference() const noexcept = 0;
	constexpr virtual const reference_type& add_rreference() const noexcept = 0;

	constexpr cv_qualifier get_cv_qualifier() const noexcept
	{
		return cv;
	}
};
