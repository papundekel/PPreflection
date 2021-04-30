#pragma once
#include "PP/concepts/bounded_array.hpp"
#include "PP/extent.hpp"

#include "../known_bound_array_type.h"
#include "basic_array_type.hpp"
#include "basic_complete_object_type.hpp"

namespace PPreflection::detail
{
	template <typename T>
	class basic_known_bound_array_type final
		: public basic_array_type<
			  T,
			  basic_complete_object_type<T, known_bound_array_type>>
	{
		static_assert(PP::concepts::bounded_array<T>);

		constexpr PP::size_t get_extent() const noexcept override final
		{
			return PP::extent(PP::type<T>);
		}
	};
}
