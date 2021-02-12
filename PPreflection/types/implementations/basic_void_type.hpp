#pragma once
#include "../void_type.h"
#include "basic_cv_qualifiable_type.hpp"
#include "concepts/void.hpp"

namespace PPreflection::detail
{
	template <typename T>
	class basic_void_type final : public basic_cv_qualifiable_type<T, void_type>
	{
		static_assert(PP::concepts::void_type<T>);
	};
}
