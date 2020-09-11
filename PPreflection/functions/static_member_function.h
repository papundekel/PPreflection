#pragma once
#include "maybe_static_member_function.h"

class static_member_function : public detail::maybe_static_member_function 
{
public:
	class overloaded : public detail::maybe_static_member_function::overloaded
	{
	protected:
		constexpr virtual PP::any_view<const static_member_function&> get_static_member_overloads() const noexcept = 0;

	public:
		constexpr PP::view auto get_overloads() const noexcept
		{
			return get_static_member_overloads();
		}
	};

	constexpr const overloaded& get_overloaded_function() const noexcept override = 0;
};
