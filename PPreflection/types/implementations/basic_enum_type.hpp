#pragma once
#include "basic_user_defined_type.hpp"
#include "../enum_type.h"

namespace detail
{
	template <typename T>
	class basic_enum_type final : public basic_user_defined_type<T, enum_type>
	{};
}
