#pragma once
#include "PP/concepts/non_void_fundamental.hpp"
#include "PP/tuple_find_dynamic.hpp"
#include "PP/fundamental_types.h"

#include "../../basic_named_descriptor.h"
#include "../non_void_fundamental_type.h"
#include "basic_non_array_object_type.hpp"

namespace PPreflection::detail
{
	template <typename T>
	class basic_non_void_fundamental_type final : public basic_named_descriptor<T, basic_non_array_object_type<T, non_void_fundamental_type>>
	{
		static_assert(PP::concepts::non_void_fundamental<T>);
	};
}
