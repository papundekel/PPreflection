#pragma once
#include "dynamic_reference.h"
#include "reflect.h"
#include "reflect_polymorphic.hpp"
#include "types/non_union_class_type.h"

namespace PPreflection
{
	dynamic_reference dynamic_polymorphic_reference(auto&& obj)
	{
		constexpr auto T = ~PP_DECLTYPE(obj);

		if constexpr (PP::is_non_union_class(T))
			return reflect_polymorphic(typeid(obj)).reference_conversion_to_derived(reflect(T))(PP_FORWARD(obj));
		else
			return PP_FORWARD(obj);
	}
}
