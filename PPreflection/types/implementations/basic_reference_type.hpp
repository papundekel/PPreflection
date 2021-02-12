#pragma once
#include "../reference_type.h"
#include "basic_type.hpp"
#include "concepts/reference.hpp"

namespace PPreflection::detail
{
	template <typename T>
	class basic_reference_type final : public basic_type<T, reference_type>
	{
		static_assert(PP::concepts::reference<T>);

		constexpr const referencable_type& remove_reference() const noexcept override final
		{
			return this->reflect(!PP::type<T>);
		}

		constexpr bool is_lvalue() const noexcept override final
		{
			return PP::concepts::lvalue_reference<T>;
		}
	};
}
