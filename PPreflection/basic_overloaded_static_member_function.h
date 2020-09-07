#pragma once
#include "basic_overloaded_function.h"
#include "overloaded_static_member_function.h"

namespace detail
{
	template <typename ID, typename Class, typename Functions>
	class basic_overloaded_static_member_function final : public basic_overloaded_function<ID, Functions, overloaded_static_member_function>
	{
	public:
		constexpr any_view<const static_member_function&> get_static_member_overloads() const noexcept override final
		{
			return reflect_many<Functions, static_member_function>();
		}

		constexpr const type& get_enclosing_class() const noexcept override final
		{
			return reflect<Class, type>();
		}
	};
}
