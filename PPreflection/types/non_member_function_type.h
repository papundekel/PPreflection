#pragma once
#include "referencable_type.h"
#include "any_iterator.hpp"
#include "parameter_type_reference.h"
#include "return_type_reference.h"

class non_member_function_type : public referencable_type
{
public:
	constexpr virtual return_type_reference return_type() const noexcept = 0;
	constexpr virtual PP::any_view<parameter_type_reference> parameter_types() const noexcept = 0;
	constexpr virtual bool is_noexcept() const noexcept = 0;
};
