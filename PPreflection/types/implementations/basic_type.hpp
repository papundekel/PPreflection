#pragma once
#include "../type.h"

namespace detail
{
	template <typename T, typename Base>
	class basic_type : public Base
	{};
}