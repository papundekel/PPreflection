#pragma once
#include <string_view>
#include "simple_ostream.h"
#include "descriptor.h"

namespace detail
{
	template <typename ID, typename Base>
	class basic_overloaded_function : public Base
	{
	public:
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
