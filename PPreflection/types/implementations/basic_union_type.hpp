#pragma once
#include <type_traits>
#include "basic_class_type.hpp"
#include "../union_type.h"

namespace detail
{
	template <typename T>
	class basic_union_type final : public basic_class_type<T, union_type>
	{};
}
