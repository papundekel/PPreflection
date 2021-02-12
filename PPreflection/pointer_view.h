#pragma once
#include "simple_view.hpp"

namespace PPreflection
{
	template <typename T>
	using pointer_view = PP::simple_view<T*>;
}
