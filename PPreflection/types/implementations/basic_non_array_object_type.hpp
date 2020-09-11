#pragma once
#include <type_traits>
#include "basic_complete_object_type.hpp"
#include "../non_array_object_type.h"

namespace detail
{
	template <typename T, typename Base>
	class basic_non_array_object_type : public basic_complete_object_type<T, Base>
	{};
}
