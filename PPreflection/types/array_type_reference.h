#pragma once
#include "known_bound_array_type.h"
#include "unknown_bound_array_type.h"
#include "../type_disjunction_reference.h"

namespace detail
{
	using array_type_reference_helper = type_disjunction_reference<known_bound_array_type, unknown_bound_array_type>;
}

class array_type_reference : public array_type_reference_helper
{
public:
	using array_type_reference_helper::array_type_reference_helper;

	constexpr const complete_object_type& remove_extent() const noexcept
	{
		return visit([](const auto& array_type)
			{
				return array_type.remove_extent();
			});
	}
};
