#pragma once
#include <type_traits>
#include "basic_pointable_type.hpp"
#include "../referencable_type.h"

namespace PPreflection::detail
{
	template <typename T, typename Base>
	class basic_referencable_type : public basic_pointable_type<T, Base>
	{};
}
