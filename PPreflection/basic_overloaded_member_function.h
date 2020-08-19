#pragma once
#include "basic_overloaded_function.h"
#include "overloaded_member_function.h"

namespace detail
{
	template <typename ID, typename Functions>
	class basic_overloaded_member_function : public basic_overloaded_function<ID, overloaded_member_function>
	{
	public:
		constexpr simple_range<const cref_t<member_function>> get_overloads() const noexcept override final;

		constexpr const type& get_enclosing_class() const noexcept override final;
	};
}
