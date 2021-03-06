#pragma once
#include "../convertor.h"
#include "non_void_fundamental_type.h"

namespace PPreflection
{
	class arithmetic_type : public non_void_fundamental_type
	{
	public:
		constexpr virtual convertor_object promotion() const noexcept = 0;
	};
}
