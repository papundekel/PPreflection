#pragma once
#include "PP/any_iterator.hpp"
#include "PP/view_equal.hpp"

#include "descriptor.h"
#include "named_descriptor.h"
#include "PPany_view.hpp"

namespace PPreflection
{
	class user_defined_type;
	class namespace_function;

	class Namespace : public detail::named_descriptor<descriptor>
	{
		constexpr parent_descriptor_reference get_parent(void*) const noexcept override final;

	public:
		constexpr virtual const Namespace& get_parent() const noexcept = 0;

		constexpr virtual PP::any_view<PP::iterator_category::ra, const Namespace&> get_namespaces() const noexcept = 0;
		constexpr virtual PP::any_view<PP::iterator_category::ra, const user_defined_type&> get_types() const noexcept = 0;
		constexpr virtual PP::any_view<PP::iterator_category::ra, const namespace_function&> get_functions() const noexcept = 0;

		constexpr void print_name_before_parent(PP::simple_ostream&) const noexcept override final
		{}
		constexpr void print_name_after_parent(PP::simple_ostream& out) const noexcept override final
		{
			out.write(get_name());
		}
		constexpr const Namespace* get_namespace(PP::string_view name) const noexcept;
		constexpr const user_defined_type* get_type(PP::string_view name) const noexcept;
		constexpr void get_function_overloads(PP::string_view name, PP::concepts::iterator auto i_out) const noexcept;

		inline dynamic_variable invoke(PP::string_view function_name, PP::any_view<PP::iterator_category::ra, const dynamic_reference&> args = {}) const noexcept;
		inline dynamic_variable invoke_qualified(PP::string_view function_name, PP::any_view<PP::iterator_category::ra, const dynamic_reference&> args = {}) const noexcept;

		class global;
	};
}
