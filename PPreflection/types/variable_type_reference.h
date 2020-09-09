#pragma once
#include "../type_disjunction_reference.h"
#include "reference_type.h"
#include "void_type.h"
#include "unknown_bound_array_type.h"
#include "known_bound_array_type.h"
#include "non_array_object_type.h"

namespace detail
{
	using variable_type_reference_base = type_disjunction_reference<
		reference_type,
		void_type,
		unknown_bound_array_type,
		known_bound_array_type,
		non_array_object_type>;
}

class variable_type_reference : public detail::variable_type_reference_base
{
public:
	template <typename T>
	constexpr variable_type_reference(T&& t)
		: detail::variable_type_reference_base(std::forward<T>(t))
	{}
};
