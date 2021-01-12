#pragma once
#include "basic_object_type.hpp"
#include "../complete_object_type.h"

namespace detail
{
	template <typename T, typename Base>
	class basic_complete_object_type : public basic_object_type<T, Base>
	{};
}
