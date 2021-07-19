#pragma once
#include "PP/any_iterator.hpp"
#include "PP/any_view.hpp"
#include "PP/view_equal.hpp"

#include "descriptor.h"
#include "dynamic_reference.h"
#include "named_descriptor.h"

namespace PPreflection
{
	class dynamic_variable;
	class user_defined_type;
	class namespace_function;

	class Namespace : public detail::named_descriptor<descriptor>
	{
		constexpr parent_descriptor_reference get_parent(
			void*) const noexcept override final;

	public:
		class global;

		constexpr virtual const Namespace& get_parent() const noexcept = 0;

		constexpr virtual PP::any_view<PP::iterator_category::ra,
									   const Namespace&>
		get_namespaces() const noexcept = 0;
		constexpr virtual PP::any_view<PP::iterator_category::ra,
									   const user_defined_type&>
		get_types() const noexcept = 0;
		constexpr virtual PP::any_view<PP::iterator_category::ra,
									   const namespace_function&>
		get_functions() const noexcept = 0;

		constexpr void print_name_before_parent(
			PP::ostream&) const noexcept override final
		{}
		constexpr void print_name_after_parent(
			PP::ostream& out) const noexcept override final
		{
			out.write(get_name());
		}
		constexpr const Namespace* get_namespace(
			PP::string_view name) const noexcept;
		constexpr const user_defined_type* get_type(
			PP::string_view name) const noexcept;

		inline dynamic_variable invoke_qualified(
			PP::string_view function_name,
			PP::concepts::view auto&& arguments) const;
		inline dynamic_variable invoke_qualified(
			PP::string_view function_name,
			const std::initializer_list<dynamic_reference>& arguments) const;

	private:
		inline dynamic_variable invoke_qualified_impl(
			PP::string_view function_name,
			PP::concepts::view auto&& arguments) const;
	};
}
