#pragma once
#include "PP/variant.hpp"

#include "type.h"

namespace PPreflection
{
	class referencable_type;
	class void_type;

	class pointable_type : public type
	{
	public:
		constexpr PP::variant<const reference_type&, const pointable_type&>
			cast_down(PP::overload_tag<type>) const noexcept override final
		{
			return { PP::placeholder, *this };
		}
		constexpr virtual PP::variant<const void_type&,
									  const referencable_type&>
			cast_down(PP::overload_tag<pointable_type> = {}) const noexcept = 0;
	};
}
