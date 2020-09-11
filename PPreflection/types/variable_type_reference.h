#pragma once
#include "../type_disjunction_reference.hpp"
#include "void_type.h"
#include "unknown_bound_array_type.h"
#include "known_bound_array_type.h"


/*namespace detail
{
	using variable_type_reference_base = type_disjunction_reference<
		reference_type,
		void_type,
		known_bound_array_type,
		non_array_object_type>;
}

class variable_type_reference : public detail::variable_type_reference_base
{
public:
	using detail::variable_type_reference_base::variable_type_reference_base;
};
*/