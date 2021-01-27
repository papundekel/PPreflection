#pragma once
#include <type_traits>
#include "basic_object_type.hpp"
#include "../complete_object_type.h"

namespace detail
{
	template <typename T, typename Base>
	class basic_array_type : public Base
	{
	public:
		constexpr const complete_object_type& remove_extent() const noexcept
		{
			return type::reflect(PP::type<std::remove_extent_t<T>>);
		}
	};
}
