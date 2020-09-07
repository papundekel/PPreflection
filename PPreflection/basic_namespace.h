#pragma once
#include "namespace_t.h"
#include "reflect.h"

namespace detail
{
	template <typename ID, typename Types, typename Functions>
	class basic_namespace : public namespace_t
	{
	public:
		constexpr any_view<const type&> get_types() const noexcept override final
		{
			return reflect_many<Types, type>();
		}
		constexpr any_view<const overloaded_namespace_function&> get_functions() const noexcept override final
		{
			return reflect_many<Functions, overloaded_namespace_function>();
		}
		constexpr void print_name(simple_ostream& out) const noexcept override final
		{
			out.write(descriptor::reflect_name<ID>());
		}
		constexpr bool has_name(std::string_view name) const noexcept override final
		{
			return descriptor::reflect_name<ID>() == name;
		}
	};
}
