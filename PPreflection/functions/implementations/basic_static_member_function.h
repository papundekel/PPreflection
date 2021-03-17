#pragma once
#include "../static_member_function.h"
#include "basic_static_function.h"

namespace PPreflection::detail
{
	template <auto f>
	class basic_static_member_function : public basic_static_function<f, static_member_function>
	{
		
	};
}
