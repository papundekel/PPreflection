#pragma once
#include "basic_user_defined_type.hpp"
#include "../class_type.h"

namespace detail
{
	template <typename T, typename Base>
	class basic_class_type : public basic_user_defined_type<T, Base>
	{};
}
