#pragma once
#include "PP/concepts/derived_from.hpp"
#include "PP/view_equal.hpp"

#include "descriptor.h"

namespace PPreflection::detail
{
	template <typename Base>
	class named_descriptor : public Base
	{
		static_assert(PP::concepts::derived_from<Base, descriptor>);

	public:
		constexpr virtual PP::string_view get_name() const noexcept = 0;

		constexpr bool has_name(
			PP::string_view name) const noexcept override final
		{
			return PP::view_equal(get_name(), name);
		}
	};
}
