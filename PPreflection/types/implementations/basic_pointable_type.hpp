#pragma once
#include "basic_type.hpp"
#include "../pointable_type.h"

namespace detail
{
	template <typename T, typename Base>
	class basic_pointable_type : public basic_type<T, Base>
	{};
}
