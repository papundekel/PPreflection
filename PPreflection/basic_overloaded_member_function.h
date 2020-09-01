#pragma once
#include "basic_overloaded_function.h"

namespace detail
{
	template <typename ID, typename Functions, typename Base>
	class basic_overloaded_member_function_base : public basic_overloaded_function<ID, Functions, Base>
	{
	public:
		constexpr pointer_view<const cref_t<member_function>> get_member_function_overloads() const noexcept override final
		{
			return reflect_many<Functions, member_function>();
		}

		constexpr const type& get_enclosing_class() const noexcept override final
		{
			return get_member_function_overloads().begin()->get().get_enclosing_class();
		}
	};

	template <typename ID, typename Functions>
	class basic_overloaded_member_function : public basic_overloaded_member_function_base<ID, Functions, overloaded_member_function>
	{};
}
