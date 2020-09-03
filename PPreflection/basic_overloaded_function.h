#pragma once
#include <string_view>
#include "simple_ostream.h"
#include "descriptor.h"

namespace detail
{
	struct empty_id {};

	template <typename ID, typename F, typename Base>
	class basic_overloaded_function : public Base
	{
	protected:
		using Functions = F;
	public:
		constexpr void print_name(simple_ostream& out) const noexcept override
		{
			out.write(descriptor::reflect_name<ID>());
		}
		constexpr bool has_name(std::string_view name) const noexcept override
		{
			return descriptor::reflect_name<ID>() == name;
		}
		constexpr pointer_view<const cref_t<function>> get_function_overloads() const noexcept override final
		{
			return reflect_many<Functions, function>();
		}
	};
	template <typename F, typename Base>
	class basic_overloaded_function<empty_id, F, Base> : public Base
	{
	protected:
		using Functions = F;
	public:
		constexpr pointer_view<const cref_t<function>> get_function_overloads() const noexcept override final
		{
			return reflect_many<Functions, function>();
		}
	};
}
