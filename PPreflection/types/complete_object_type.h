#pragma once
#include "object_type.h"

namespace PPreflection
{
	class complete_object_type : public object_type
	{
	public:
		constexpr virtual std::size_t size() const noexcept = 0;
		constexpr virtual void destroy(void* ptr) const noexcept = 0;
	};
}
