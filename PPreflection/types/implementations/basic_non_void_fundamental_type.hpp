#pragma once
#include <type_traits>
#include "basic_non_array_object_type.hpp"
#include "../non_void_fundamental_type.h"

namespace detail
{
	template <typename T>
	class basic_non_void_fundamental_type final : public basic_non_array_object_type<T, non_void_fundamental_type>
	{};
}
