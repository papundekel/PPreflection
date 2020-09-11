#pragma once
#include <type_traits>
#include "basic_array_type.hpp"
#include "basic_complete_object_type.hpp"
#include "../known_bound_array_type.h"

namespace detail
{
	template <typename T>
	class basic_known_bound_array_type final : public basic_array_type<T, basic_complete_object_type<T, known_bound_array_type>>
	{};
}
