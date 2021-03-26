#pragma once
#include "../non_conversion_member_function.h"
#include "basic_member_function.h"

namespace PPreflection::detail
{
	template <auto mf>
	class basic_non_conversion_member_function : public basic_member_function<mf, non_conversion_member_function>
	{
		dynamic_variable invoke_unsafe_member(dynamic_reference caller, PP::any_iterator<PP::iterator_category::ra, dynamic_reference> arg_iterator) const noexcept override final
		{
			return this->invoke_helper(
				[this, caller](auto&&... args) -> decltype(auto)
				{
					return (caller.cast_unsafe(this->caller_type).*mf)(PP_FORWARD(args)...);
				}, arg_iterator, this->parameter_types);
		}
	};
}
