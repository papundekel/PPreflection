#pragma once
#include <type_traits>
#include "basic_non_array_object_type.hpp"
#include "../pointer_type.h"

namespace detail
{
	template <typename T>
	class basic_pointer_type final : public basic_non_array_object_type<T, pointer_type>
	{
		static_assert(std::is_pointer_v<T>);

		constexpr const pointable_type& remove_pointer() const noexcept override final
		{
			return type::reflect(PP::type<std::remove_pointer_t<T>>);
		}
	};
}
