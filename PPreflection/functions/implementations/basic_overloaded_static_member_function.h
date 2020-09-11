#pragma once
#include "basic_overloaded_function.h"
#include "../static_member_function.h"

namespace detail
{
	template <typename ID, typename Class, typename Functions>
	class basic_overloaded_static_member_function final : public basic_overloaded_function<ID, Functions, static_member_function>
	{
	public:
		constexpr PP::any_view<const static_member_function&> get_static_member_overloads() const noexcept override final
		{
			return reflect_many<Functions, const static_member_function&>();
		}

		constexpr const class_type& get_parent() const noexcept override final
		{
			return type::reflect<Class>();
		}
	};
}
