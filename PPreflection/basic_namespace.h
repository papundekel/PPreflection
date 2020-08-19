#pragma once
#include "namespace_t.h"

namespace detail
{
	template <typename ID, typename Types, typename Functions>
	class basic_namespace : public namespace_t
	{
	public:
		constexpr simple_range<const cref_t<type>> get_types() const noexcept override final;
		constexpr simple_range<const cref_t<namespace_function>> get_functions() const noexcept override final;
		constexpr void print_name(simple_ostream& out) const noexcept override final;
		constexpr bool has_name(std::string_view name) const noexcept override final;
	};
}
