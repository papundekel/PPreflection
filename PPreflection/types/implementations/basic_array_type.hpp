#pragma once
#include "PP/remove_extent.hpp"

#include "../complete_object_type.h"
#include "basic_object_type.hpp"

namespace PPreflection::detail
{
	template <typename T, typename Base>
	class basic_array_type : public Base
	{
	public:
		constexpr const complete_object_type& remove_extent() const noexcept
		{
			return type::reflect | PP::remove_extent <<= PP::type<T>;
		}
	};
}
