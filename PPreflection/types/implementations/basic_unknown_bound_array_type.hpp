#pragma once
#include "PP/concepts/unbounded_array.hpp"

#include "../unknown_bound_array_type.h"
#include "basic_array_type.hpp"
#include "basic_object_type.hpp"

namespace PPreflection::detail
{
	template <typename T>
	class basic_unknown_bound_array_type final
		: public basic_array_type<
			  T,
			  basic_object_type<T, unknown_bound_array_type>>
	{
		static_assert(PP::concepts::unbounded_array<T>);
	};
}
