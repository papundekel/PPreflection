#pragma once
#include "../object_type.h"
#include "basic_referencable_type.hpp"

namespace PPreflection::detail
{
	template <typename T, typename Base>
	class basic_object_type : public basic_referencable_type<T, Base>
	{};
}
