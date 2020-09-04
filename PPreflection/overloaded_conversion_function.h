#pragma once
#include "overloaded_member_function.h"

class conversion_function;

class overloaded_conversion_function : public overloaded_member_function
{
protected:
	constexpr virtual pointer_view<const cref_t<conversion_function>> get_conversion_overloads() const noexcept = 0;
	constexpr virtual const type& return_type() const noexcept = 0;

public:
	constexpr void print_name(simple_ostream& out) const noexcept override final
	{
		out.write("operator ");
		return_type().print_name(out);
	}
	constexpr bool has_name(std::string_view name) const noexcept override final
	{
		return name.starts_with("operator ") && return_type().has_name(name.substr(9));
	}

	constexpr dynamic_object invoke(dynamic_reference caller) const;

	constexpr const overloaded_conversion_function* is_conversion_function() const noexcept override final
	{
		return this;
	}
	constexpr PP::view auto get_overloads() const noexcept
	{
		return get_overloads_helper<conversion_function>(get_conversion_overloads());
	}
};
