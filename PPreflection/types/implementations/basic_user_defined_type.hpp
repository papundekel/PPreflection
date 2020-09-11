#pragma once
#include <type_traits>
#include "basic_non_array_object_type.hpp"
#include "../user_defined_type.h"

namespace detail
{
	template <typename T, typename Base>
	class basic_user_defined_type : public basic_non_array_object_type<T, Base>
	{};
}
