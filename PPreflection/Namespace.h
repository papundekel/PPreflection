#pragma once
#include "../PP/PP/any_iterator.hpp"
#include "descriptor.h"
#include "view_equal.hpp"

namespace PPreflection
{
	class user_defined_type;
	class overloaded_namespace_function;

	class Namespace : public descriptor
	{
	public:
		constexpr const Namespace* get_parent_implementation() const noexcept override = 0;
		constexpr virtual PP::any_view<PP::iterator_category::ra, const Namespace&> get_namespaces() const noexcept = 0;
		constexpr virtual PP::any_view<PP::iterator_category::ra, const user_defined_type&> get_types() const noexcept = 0;
		//constexpr virtual PP::any_view<PP::iterator_category::ra, const overloaded_namespace_function&> get_functions() const noexcept = 0;

		constexpr virtual PP::string_view get_name() const noexcept = 0;

		constexpr void print_name_before_parent(PP::simple_ostream& out) const noexcept override final
		{}
		constexpr void print_name_after_parent(PP::simple_ostream& out) const noexcept override final
		{
			out.write(get_name());
		}
		constexpr bool has_name(PP::string_view name) const noexcept override final
		{
			return view_equal(get_name(), name);
		}
		//constexpr const type* get_type(PP::string_view name) const noexcept;
		//constexpr const overloaded_namespace_function* get_function(PP::string_view name) const noexcept;

		struct global {};
	};
}
