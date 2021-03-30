#pragma once
#include "PP/any_iterator.hpp"

#include "../dynamic_variable.h"
#include "user_defined_type.h"

namespace PPreflection
{
	class constructor;
	class member_function;
	class conversion_function;
	class static_member_function;
	class non_union_class_type;

	class class_type : public user_defined_type
	{
	public:
		constexpr virtual PP::any_view<PP::iterator_category::ra, const constructor&> get_constructors() const noexcept = 0;
		constexpr virtual PP::any_view<PP::iterator_category::ra, const member_function&> get_member_functions() const noexcept = 0;
		constexpr virtual PP::any_view<PP::iterator_category::ra, const conversion_function&> get_conversion_functions() const noexcept = 0;
		constexpr virtual PP::any_view<PP::iterator_category::ra, const static_member_function&> get_static_member_functions() const noexcept = 0;
		constexpr virtual PP::any_view<PP::iterator_category::ra, const user_defined_type&> get_nested_types() const noexcept = 0;

		constexpr virtual const non_union_class_type* as_non_union_class() const noexcept = 0;

		inline dynamic_object create_instance(PP::any_view<PP::iterator_category::ra, dynamic_reference> args = {}) const noexcept;

		inline dynamic_object copy_initialize_same_or_derived(dynamic_reference arg) const noexcept;

		constexpr void get_member_function_overloads(PP::string_view name, PP::concepts::iterator auto i_out) const noexcept;
		constexpr void get_static_member_function_overloads(PP::string_view name, PP::concepts::iterator auto i_out) const noexcept;
		constexpr const user_defined_type* get_nested_type(PP::string_view name) const noexcept;

		constexpr void get_conversion_functions_inherited(PP::concepts::iterator auto i_out) const noexcept;

		constexpr virtual convertor_object base_pointer_conversion(const class_type& base) const noexcept = 0;
	};
}
