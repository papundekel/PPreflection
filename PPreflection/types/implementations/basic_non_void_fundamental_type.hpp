#pragma once
#include "../non_void_fundamental_type.h"
#include "basic_named_type.hpp"
#include "basic_non_array_object_type.hpp"
#include "concepts/non_void_fundamental.hpp"

namespace PPreflection::detail
{
	template <typename T>
	class basic_non_void_fundamental_type final : public basic_named_type<T, basic_non_array_object_type<T, non_void_fundamental_type>>
	{
		static_assert(PP::concepts::non_void_fundamental<T>);
	};
}
