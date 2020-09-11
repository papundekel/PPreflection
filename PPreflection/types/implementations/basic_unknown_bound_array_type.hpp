#pragma once
#include <type_traits>
#include "basic_array_type.hpp"
#include "../unknown_bound_array_type.h"

namespace detail
{
	template <typename T>
	class basic_unknown_bound_array_type final : public basic_array_type<T, basic_object_type<T, unknown_bound_array_type>>
	{};
}
