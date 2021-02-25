#pragma once
#include "maybe_static_member_function.h"

namespace PPreflection
{
	class static_member_function;

	class overloaded_static_member_function : public detail::maybe_static_member_function::overloaded
	{
	protected:
		constexpr virtual PP::any_view<PP::iterator_category::ra, const static_member_function&> get_static_member_overloads() const noexcept = 0;

	public:
		constexpr PP::concepts::view auto get_overloads() const noexcept
		{
			return get_static_member_overloads();
		}
	};

	class static_member_function : public detail::maybe_static_member_function
	{
	public:
		using overloaded = overloaded_static_member_function;

		constexpr const overloaded& get_overloaded_function() const noexcept override = 0;
	};
}
