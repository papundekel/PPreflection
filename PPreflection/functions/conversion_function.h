#pragma once
#include "member_function.h"

class conversion_function;

class overloaded_conversion_function : public member_function::overloaded
{
protected:
	constexpr virtual PP::any_view<const conversion_function&> get_conversion_overloads() const noexcept = 0;
	constexpr virtual return_type_reference return_type() const noexcept = 0;

public:
	constexpr virtual void print_name_after_parent(PP::simple_ostream& out) const noexcept override final
	{
		out.write("operator ");
		const descriptor& rt = return_type();
		rt.print_name(out);
	}
	constexpr bool has_name(std::string_view name) const noexcept override final
	{
		const descriptor& rt = return_type();
		return name.starts_with("operator ") && rt.has_name(name.substr(9));
	}

	inline dynamic_variable invoke(dynamic_reference caller) const;

	constexpr PP::view auto get_overloads() const noexcept
	{
		return get_conversion_overloads();
	}
};

class conversion_function : public member_function
{
protected:
	constexpr virtual dynamic_variable invoke_unsafe_conversion(dynamic_reference caller) const noexcept = 0;

	inline dynamic_variable invoke_unsafe_member(dynamic_reference caller, PP::any_iterator<const dynamic_reference&>) const noexcept override final
	{
		return invoke_unsafe_conversion(caller);
	}
public:
	constexpr virtual bool is_explicit() const noexcept = 0;

	inline dynamic_variable invoke(dynamic_reference caller) const
	{
		if (can_invoke(caller.get_type()))
			return invoke_unsafe_conversion(caller);
		else
			return dynamic_variable::create_invalid(dynamic_object::invalid_code::implicit_conversion_error);
	}

	using overloaded = overloaded_conversion_function;
	friend overloaded_conversion_function;

	constexpr const overloaded& get_overloaded_function() const noexcept override = 0;
};
