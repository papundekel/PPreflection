#pragma once
#include "../referencable_type.h"
#include "basic_pointable_type.hpp"

namespace PPreflection::detail
{
	template <typename T, typename Base>
	class basic_referencable_type : public basic_pointable_type<T, Base>
	{};
}
