#pragma once
#include "PP/concepts/union.hpp"

#include "../union_type.h"
#include "basic_class_type.hpp"

namespace PPreflection::detail
{
	template <typename T>
	class basic_union_type final : public basic_class_type<T, union_type>
	{
		static_assert(PP::concepts::union_type<T>);
	};
}
