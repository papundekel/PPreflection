#pragma once
#include "referencable_type.h"
#include "cv_qualifier.hpp"

namespace PPreflection
{
	class object_type : public referencable_type
	{
	public:
		constexpr virtual std::size_t alignment() const noexcept = 0;

		constexpr virtual PP::cv_qualifier get_cv_qualifier() const noexcept = 0;
	};
}
