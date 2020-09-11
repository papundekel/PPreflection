#pragma once
#include <type_traits>
#include "basic_referencable_type.hpp"
#include "basic_cv_qualifiable_type.hpp"
#include "../object_type.h"

namespace detail
{
	template <typename T, typename Base>
	class basic_object_type : public basic_cv_qualifiable_type<T, basic_referencable_type<T, Base>>
	{};
}
