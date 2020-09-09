#pragma once
#include "basic_overloaded_function.h"
#include "first_pack.h"
#include "get_member_function_info.h"

namespace detail
{
	template <typename ID, typename Functions, typename Base>
	class basic_overloaded_member_function_base : public basic_overloaded_function<ID, Functions, Base>
	{
	public:
		constexpr any_view<const member_function&> get_member_function_overloads() const noexcept override final
		{
			return reflect_many<Functions, member_function>();
		}

		constexpr const type& get_parent() const noexcept override final
		{
			return reflect<typename get_member_function_info<decltype(get_value<get_type<first_pack<Functions>>>())>::Class, type>();
		}
	};

	template <typename ID, typename Functions>
	class basic_overloaded_member_function final : public basic_overloaded_member_function_base<ID, Functions, overloaded_member_function>
	{};
}
