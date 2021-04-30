#pragma once
#include "PP/concepts/derived_from.hpp"

#include "../named_descriptor.h"
#include "function.h"

namespace PPreflection::detail
{
	template <typename Base>
	class named_function : public named_descriptor<Base>
	{
		static_assert(PP::concepts::derived_from<Base, function>);

	public:
		constexpr void print_name_implementation(
			PP::simple_ostream& out) const noexcept override final
		{
			out.write(this->get_name());
		}
	};
}
