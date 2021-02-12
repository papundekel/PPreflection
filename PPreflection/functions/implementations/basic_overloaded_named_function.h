#pragma once
#include "../function.h"
#include "../../basic_named_descriptor.h"

namespace PPreflection::detail
{
	template <typename ID, typename Base>
	class basic_overloaded_named_function : public basic_named_descriptor<ID, Base>
	{
		constexpr void print_name_after_parent(PP::simple_ostream& out) const noexcept override final
		{
			out.write(this->get_name());
		}
	};
}
