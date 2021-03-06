#pragma once
#include "../non_array_object_type.h"
#include "basic_complete_object_type.hpp"

namespace PPreflection::detail
{
	template <typename T, typename Base>
	class basic_non_array_object_type : public basic_complete_object_type<T, Base>
	{
		constexpr PP::size_t alignment() const noexcept override final
		{
			return alignof(T);
		}
		constexpr PP::size_t size() const noexcept override final
		{
			return sizeof(T);
		}
	};
}
