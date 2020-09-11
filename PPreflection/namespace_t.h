#pragma once
#include <string_view>
#include "descriptor.h"
#include "pointer_view.h"
#include "../PP/PP/any_iterator.hpp"

class type;
class overloaded_namespace_function;

class namespace_t : public descriptor
{
public:
	constexpr virtual const namespace_t* get_parent() const noexcept = 0;

	constexpr virtual PP::any_view<const type&> get_types() const noexcept = 0;
	constexpr virtual PP::any_view<const overloaded_namespace_function&> get_functions() const noexcept = 0;

	constexpr void print_name_before_parent(PP::simple_ostream& out) const noexcept override final
	{}

	constexpr const type* get_type(std::string_view name) const noexcept;
	constexpr const overloaded_namespace_function* get_function(std::string_view name) const noexcept;

	struct global {};

private:
	constexpr const descriptor* get_parent_implementation() const noexcept override final
	{
		return get_parent();
	}
};
