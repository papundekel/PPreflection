#pragma once
#include <type_traits>
#include "basic_type.hpp"
#include "../reference_type.h"

namespace detail
{
	template <typename T>
	class basic_reference_type final : public basic_type<T, reference_type>
	{
		static_assert(std::is_reference_v<T>);

		constexpr const referencable_type& remove_reference() const noexcept override final
		{
			return type::reflect<std::remove_reference_t<T>>();
		}

		constexpr bool is_lvalue() const noexcept override final
		{
			return std::is_lvalue_reference_v<T>;
		}
	};
}
