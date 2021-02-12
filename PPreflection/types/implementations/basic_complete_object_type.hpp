#pragma once
#include "../complete_object_type.h"
#include "basic_object_type.hpp"

namespace PPreflection::detail
{
	template <typename T, typename Base>
	class basic_complete_object_type : public basic_object_type<T, Base>
	{};
}
