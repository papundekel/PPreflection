#pragma once
#include "overload_resolution.h"

#include "initialization.h"

template <typename Function>
inline void PPreflection::viable_function<Function>::make_conversion_sequences(
	PP::concepts::view auto&& argument_types,
	bool can_use_user_defined)
{
	auto parameter_types = get_function().parameter_types_olr();
	auto parameter_types_i = parameter_types.begin();

	for (const reference_type& from_type : PP_F(argument_types))
	{
		conversion_sequences.push_back(
			initialization_sequence(*parameter_types_i,
		                            from_type,
		                            can_use_user_defined));

		++parameter_types_i;
	}
}
