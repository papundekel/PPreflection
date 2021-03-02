#pragma once
#include "../pointable_type.h"
#include "basic_type.hpp"

namespace PPreflection::detail
{
	template <typename T, typename Base>
	class basic_pointable_type : public basic_type<T, Base>
	{};
}
