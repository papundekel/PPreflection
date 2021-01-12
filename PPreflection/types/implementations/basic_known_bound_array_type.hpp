#pragma once
#include <type_traits>
#include "basic_array_type.hpp"
#include "basic_complete_object_type.hpp"
#include "../known_bound_array_type.h"

namespace detail
{
	template <typename T>
	class basic_known_bound_array_type final : public basic_array_type<T, basic_complete_object_type<T, known_bound_array_type>>
	{
		static_assert(std::is_bounded_array_v<T>);

		constexpr std::size_t get_extent() const noexcept override final
		{
			return std::extent_v<T>;
		}
	};
}
