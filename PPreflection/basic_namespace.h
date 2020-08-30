#pragma once
#include "namespace_t.h"

namespace detail
{
	template <typename ID, typename Types, typename Functions>
	class basic_namespace : public namespace_t
	{
	public:
		constexpr pointer_view<const cref_t<type>> get_types() const noexcept override final;
		constexpr pointer_view<const cref_t<overloaded_namespace_function>> get_functions() const noexcept override final;
		constexpr void print_name(simple_ostream& out) const noexcept override final;
		constexpr bool has_name(std::string_view name) const noexcept override final;
	};
}
