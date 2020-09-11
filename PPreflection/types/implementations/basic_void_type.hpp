#pragma once
#include "basic_cv_qualifiable_type.hpp"
#include "../void_type.h"

namespace detail
{
	template <typename T>
	class basic_void_type final : public basic_cv_qualifiable_type<T, void_type>
	{
		static_assert(std::is_void_v<T>);
	};
}
