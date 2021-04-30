#pragma once
#include "cv_type.h"
#include "dynamic_lvalue_reference_type.h"
#include "dynamic_reference_type.h"
#include "dynamic_rvalue_reference_type.h"

namespace PPreflection
{
	constexpr dynamic_lvalue_reference_type make_lreference_type(
		cv_type<referencable_type> t)
	{
		return dynamic_lvalue_reference_type(t);
	}
	constexpr dynamic_rvalue_reference_type make_rreference_type(
		cv_type<referencable_type> t)
	{
		return dynamic_rvalue_reference_type(t);
	}
	constexpr auto make_reference_type(PP::concepts::value auto	  lvalue,
									   cv_type<referencable_type> t)
	{
		if constexpr (PP_GET_VALUE(lvalue))
			return make_lreference_type(t);
		else
			return make_rreference_type(t);
	}
	constexpr dynamic_reference_type make_reference_type(
		bool					   lvalue,
		cv_type<referencable_type> t)
	{
		return dynamic_reference_type(t, lvalue);
	}
}
