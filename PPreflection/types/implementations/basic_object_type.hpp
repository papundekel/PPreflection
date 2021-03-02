#pragma once
#include "../object_type.h"
#include "basic_referencable_type.hpp"
#include "basic_cv_qualifiable_type.hpp"

namespace PPreflection::detail
{
	template <typename T, typename Base>
	class basic_object_type : public basic_referencable_type<T, Base>
	{};
}
