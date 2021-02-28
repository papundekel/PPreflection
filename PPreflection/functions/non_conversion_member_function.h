#pragma once
#include "../named_descriptor.h"
#include "member_function.h"

namespace PPreflection
{
	class overloaded_non_conversion_member_function : public detail::named_descriptor<member_function::overloaded>
	{

	};

	class non_conversion_member_function : public member_function
	{
	public:
		using overloaded = overloaded_non_conversion_member_function;

		constexpr const overloaded& get_overloaded_function() const noexcept override = 0;
	};
}
