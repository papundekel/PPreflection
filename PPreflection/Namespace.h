#pragma once
#include "../PP/PP/any_iterator.hpp"
#include "descriptor.h"
#include "named_descriptor.h"
#include "PPany_view.hpp"
#include "view_equal.hpp"

namespace PPreflection
{
	class user_defined_type;
	class overloaded_namespace_function;

	class Namespace : public detail::named_descriptor<descriptor>
	{
	public:
		constexpr const Namespace& get_parent() const noexcept override = 0;

		constexpr virtual PP::any_view<PP::iterator_category::ra, const Namespace&> get_namespaces() const noexcept = 0;
		constexpr virtual PP::any_view<PP::iterator_category::ra, const user_defined_type&> get_types() const noexcept = 0;
		constexpr virtual PP::any_view<PP::iterator_category::ra, const overloaded_namespace_function&> get_functions() const noexcept = 0;

		constexpr void print_name_before_parent(PP::simple_ostream& out) const noexcept override final
		{}
		constexpr void print_name_after_parent(PP::simple_ostream& out) const noexcept override final
		{
			out.write(get_name());
		}
		constexpr const Namespace* get_namespace(PP::string_view name) const noexcept;
		constexpr const user_defined_type* get_type(PP::string_view name) const noexcept;
		constexpr const overloaded_namespace_function* get_function(PP::string_view name) const noexcept;

		class global;
	};
}
