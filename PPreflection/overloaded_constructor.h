#pragma once
#include "overloaded_maybe_static_member_function.h"
#include "../PP/PP/transform_view.hpp"
#include "../PP/PP/id.hpp"

class constructor;
class one_parameter_converting_constructor;

class overloaded_constructor : public detail::overloaded_maybe_static_member_function
{
protected:
	constexpr virtual any_view<const one_parameter_converting_constructor&> get_one_parameter_converting_constructor_overloads() const noexcept = 0;
	constexpr virtual any_view<const constructor&> get_constructor_overloads() const noexcept = 0;

public:
	constexpr void print_name(simple_ostream& out) const noexcept override final
	{
		get_parent().print_name(out);
	}
	constexpr bool has_name(std::string_view name) const noexcept override final
	{
		return get_parent().has_name(name);
	}
	constexpr PP::view auto get_overloads() const noexcept
	{
		return get_constructor_overloads();
	}
};
