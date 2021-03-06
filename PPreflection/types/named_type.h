#pragma once
#include "PP/concepts/derived_from.hpp"

#include "../named_descriptor.h"
#include "type.h"

namespace PPreflection::detail
{
	template <typename Base>
	class named_type : public named_descriptor<Base>
	{
		static_assert(PP::concepts::derived_from<Base, type>);
		
	public:
		constexpr void print_name_prefix(PP::simple_ostream& out) const noexcept override final
		{
			out.write(this->get_name());
		}
		constexpr void print_name_suffix(PP::simple_ostream&) const noexcept override final
		{}
	};
}
