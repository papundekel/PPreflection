#pragma once
#include <string_view>
#include "descriptor.h"
#include "pointer_view.h"
#include "../PP/PP/any_iterator.hpp"

class user_defined_type;
class overloaded_namespace_function;

class Namespace : public descriptor
{
public:
	constexpr virtual const Namespace* get_parent() const noexcept = 0;

	constexpr virtual PP::any_view<const Namespace&> get_namespaces() const noexcept = 0;
	constexpr virtual PP::any_view<const user_defined_type&> get_types() const noexcept = 0;
	constexpr virtual PP::any_view<const overloaded_namespace_function&> get_functions() const noexcept = 0;

	constexpr virtual std::string_view get_name() const noexcept = 0;

	constexpr void print_name_before_parent(PP::simple_ostream& out) const noexcept override final
	{}
	constexpr void print_name_after_parent(PP::simple_ostream& out) const noexcept override final
	{
		out.write(get_name());
	}
	constexpr bool has_name(std::string_view name) const noexcept override final
	{
		return get_name() == name;
	}
	//constexpr const type* get_type(std::string_view name) const noexcept;
	//constexpr const overloaded_namespace_function* get_function(std::string_view name) const noexcept;

	struct global {};

private:
	constexpr const descriptor* get_parent_implementation() const noexcept override final
	{
		return get_parent();
	}
};
