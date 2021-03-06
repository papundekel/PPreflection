#pragma once
#include "PP/cv_qualifier.hpp"
#include "PP/size_t.hpp"

#include "referencable_type.h"

namespace PPreflection
{
	class object_type : public referencable_type
	{
	public:
		constexpr virtual PP::size_t alignment() const noexcept = 0;
	};
}
