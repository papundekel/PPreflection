#pragma once
#include <string_view>
#include "descriptor.h"
#include "../PP/PP/any_iterator.hpp"

namespace detail
{
	struct empty_id {};

	template <typename F, typename Base>
	class basic_overloaded_function_base : public Base
	{
	protected:
		using Functions = F;
	public:
		constexpr PP::any_view<const function&> get_function_overloads() const noexcept override final
		{
			return reflect_many<Functions, function>();
		}
	};

	template <typename ID, typename F, typename Base>
	class basic_overloaded_function : public basic_overloaded_function_base<F, Base>
	{
	public:
		constexpr void print_name(PP::simple_ostream& out) const noexcept override
		{
			out.write(descriptor::reflect_name<ID>());
		}
		constexpr bool has_name(std::string_view name) const noexcept override
		{
			return descriptor::reflect_name<ID>() == name;
		}
	};
	template <typename F, typename Base>
	class basic_overloaded_function<empty_id, F, Base> : public basic_overloaded_function_base<F, Base>
	{};
}
