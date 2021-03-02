#pragma once
#include "PP/concepts/pointer_to_member.hpp"

#include "../pointer_to_member_type.h"
#include "basic_non_array_object_type.hpp"

namespace PPreflection::detail
{
	template <typename T>
	class basic_pointer_to_member_type final : public basic_non_array_object_type<T, pointer_to_member_type>
	{
		static_assert(PP::concepts::pointer_to_member<T>);
	};
}
