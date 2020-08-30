#pragma once
#include "basic_overloaded_function.h"
#include "overloaded_namespace_function.h"

namespace detail
{
	template <typename ID, typename Namespace, typename Functions>
	class basic_overloaded_namespace_function : public basic_overloaded_function<ID, overloaded_namespace_function>
	{
	public:
		constexpr simple_range<const cref_t<namespace_function>> get_overloads() const noexcept override final;

		constexpr const namespace_t& get_enclosing_namespace() const noexcept override final;
	};
}
