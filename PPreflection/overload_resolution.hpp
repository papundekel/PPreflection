#pragma once
#include "overload_resolution.h"

#include "initialization.h"

constexpr void PPreflection::viable_function::make_conversion_sequences(PP::concepts::view auto&& argument_types, bool can_use_user_defined)
{
	auto parameter_types = f.get().parameter_types_olr();
	auto parameter_types_i = parameter_types.begin();

	for (const reference_type& from_type : PP_FORWARD(argument_types))
	{
		conversion_sequences.push_back(initialization_sequence(*parameter_types_i, from_type, can_use_user_defined));

		++parameter_types_i;
	}
}
