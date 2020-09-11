#pragma once
#include <type_traits>
#include "basic_non_array_object_type.hpp"
#include "../pointer_to_member_type.h"

namespace detail
{
	template <typename T>
	class basic_pointer_to_member_type final : public basic_non_array_object_type<T, pointer_to_member_type>
	{};
}
