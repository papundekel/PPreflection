#pragma once
#include "basic_overloaded_function.h"
#include "../member_function.h"
#include "first_pack.hpp"
#include "get_member_function_info.hpp"

namespace detail
{
	template <typename ID, typename Functions, typename Base>
	class basic_overloaded_member_function_base : public basic_overloaded_function<ID, Functions, Base>
	{
	public:
		constexpr PP::any_view<const member_function&> get_member_function_overloads() const noexcept override final
		{
			return reflect_many<Functions, const member_function&>();
		}

		constexpr const class_type& get_parent() const noexcept override final
		{
			return type::reflect<typename PP::get_member_function_info<decltype(PP::get_value<PP::get_type<PP::first_pack<Functions>>>())>::Class>();
		}
	};

	template <typename ID, typename Functions>
	class basic_overloaded_member_function final : public basic_overloaded_member_function_base<ID, Functions, member_function>
	{};
}
