#pragma once
#include "user_defined_type.h"
#include "any_iterator.hpp"
#include "../dynamic_variable.h"

namespace PPreflection
{
	class overloaded_constructor;
	class overloaded_member_function;
	class overloaded_static_member_function;
	class non_union_class_type;

	class class_type : public user_defined_type
	{
	public:
		constexpr virtual const overloaded_constructor& get_constructors() const noexcept = 0;
		constexpr virtual PP::any_view<PP::iterator_category::ra, const overloaded_member_function&> get_member_functions() const noexcept = 0;
		constexpr virtual PP::any_view<PP::iterator_category::ra, const overloaded_static_member_function&> get_static_member_functions() const noexcept = 0;
		constexpr virtual PP::any_view<PP::iterator_category::ra, const user_defined_type&> get_nested_classes() const noexcept = 0;

		constexpr virtual const non_union_class_type* as_non_union_class() const noexcept = 0;

		inline dynamic_variable create_instance(PP::any_view<PP::iterator_category::ra, const dynamic_reference&> args = {}) const noexcept;
	};
}
