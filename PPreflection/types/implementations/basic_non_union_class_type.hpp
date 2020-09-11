#pragma once
#include <type_traits>
#include "basic_class_type.hpp"
#include "../non_union_class_type.h"

namespace detail
{
	template <typename T>
	class basic_non_union_class_type final : public basic_class_type<T, non_union_class_type>
	{};
}
