#pragma once
#include "PP/view_prefix.hpp"

#include "member_function.h"

namespace PPreflection
{
	class conversion_function : public member_function
	{
	protected:
		constexpr virtual dynamic_variable invoke_unsafe_conversion(dynamic_reference caller) const noexcept = 0;

		dynamic_variable invoke_unsafe_member(dynamic_reference caller, PP::any_iterator<PP::iterator_category::ra, const dynamic_reference&>) const noexcept override final
		{
			return invoke_unsafe_conversion(caller);
		}
	public:
		constexpr virtual bool is_explicit() const noexcept = 0;

		dynamic_variable invoke(dynamic_reference caller) const noexcept
		{
			if (can_invoke(caller.get_type()))
				return invoke_unsafe_conversion(caller);
			else
				return dynamic_variable::create_invalid(dynamic_object::invalid_code::implicit_conversion_error);
		}
	};
}
