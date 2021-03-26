#pragma once
#include "PP/view_prefix.hpp"

#include "member_function.h"

namespace PPreflection
{
	class conversion_function : public member_function
	{
	protected:
		constexpr virtual dynamic_variable invoke_unsafe(dynamic_reference caller) const noexcept = 0;

		dynamic_variable invoke_unsafe(dynamic_reference caller, PP::any_iterator<PP::iterator_category::ra, dynamic_reference>) const noexcept override final
		{
			return invoke_unsafe(caller);
		}
	public:
		constexpr virtual bool is_explicit() const noexcept = 0;

		dynamic_variable invoke(dynamic_reference) const noexcept
		{
			return dynamic_variable::create_invalid(dynamic_object::invalid_code::implicit_conversion_error);
		}
	};
}
