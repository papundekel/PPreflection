#pragma once
#include "PP/cv_qualifier.hpp"

#include "type.h"

namespace PPreflection
{
	class dynamic_pointer_type;
	class referencable_type;
	class void_type;

	class pointable_type : public type
	{
	public:
		constexpr PP::variant<const reference_type&, const pointable_type&> cast_down(PP::overload_tag<type>) const noexcept override final
		{
			return {PP::placeholder, *this};
		}
		constexpr virtual PP::variant<const void_type&, const referencable_type&> cast_down(PP::overload_tag<pointable_type> = {}) const noexcept = 0;

		constexpr bool can_be_pointer_initialized(const pointable_type&) const noexcept
		{
			return true; // TODO
		}
	};
}
