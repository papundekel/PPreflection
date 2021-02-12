#pragma once
#include "../known_bound_array_type.h"
#include "basic_array_type.hpp"
#include "basic_complete_object_type.hpp"
#include "concepts/bounded_array.hpp"
#include "extent.hpp"

namespace PPreflection::detail
{
	template <typename T>
	class basic_known_bound_array_type final : public basic_array_type<T, basic_complete_object_type<T, known_bound_array_type>>
	{
		static_assert(PP::concepts::bounded_array<T>);

		constexpr size_t get_extent() const noexcept override final
		{
			return extent(PP::type<T>);
		}
	};
}
