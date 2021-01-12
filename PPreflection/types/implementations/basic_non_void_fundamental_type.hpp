#pragma once
#include <type_traits>
#include "basic_non_array_object_type.hpp"
#include "../non_void_fundamental_type.h"
#include "basic_named_type.hpp"

namespace detail
{
	template <typename T>
	class basic_non_void_fundamental_type final : public basic_named_type<T, basic_non_array_object_type<T, non_void_fundamental_type>>
	{
		static_assert(std::is_fundamental_v<T> && !std::is_void_v<T>);
	};
}
