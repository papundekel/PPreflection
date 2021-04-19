#pragma once
#include "PP/concepts/derived_from.hpp"
#include "PP/remove_cv.hpp"

#include "descriptor.h"

namespace PPreflection::detail
{
	template <typename ID, typename Base>
	class basic_named_descriptor : public Base
	{
		static_assert(PP::concepts::derived_from<Base, descriptor>);

	protected:
		constexpr PP::string_view get_name() const noexcept override final
		{
			return this->reflect_name(~PP::type<ID>);
		}
	};
}
