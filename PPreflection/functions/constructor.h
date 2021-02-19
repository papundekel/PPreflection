#pragma once
#include "maybe_static_member_function.h"

namespace PPreflection
{
	class one_parameter_converting_constructor;
	class constructor;

	class overloaded_constructor : public detail::maybe_static_member_function::overloaded
	{
	protected:
		constexpr virtual PP::any_view<PP::iterator_category::ra, const one_parameter_converting_constructor&> get_one_parameter_converting_constructor_overloads() const noexcept = 0;
		constexpr virtual PP::any_view<PP::iterator_category::ra, const constructor&> get_constructor_overloads() const noexcept = 0;

	public:
		constexpr void print_name_after_parent(PP::simple_ostream& out) const noexcept override final
		{
			get_parent().print_name(out);
		}
		constexpr bool has_name(PP::string_view name) const noexcept override final
		{
			return get_parent().has_name(name);
		}
		constexpr PP::concepts::view auto get_overloads() const noexcept
		{
			return get_constructor_overloads();
		}
	};

	class constructor : public detail::maybe_static_member_function
	{
	public:
		constexpr virtual bool is_explicit() const noexcept = 0;

		using overloaded = overloaded_constructor;

		constexpr const overloaded& get_overloaded_function() const noexcept override = 0;
	};
}
