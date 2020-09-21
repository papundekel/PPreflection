#pragma once
#include "user_defined_type.h"
#include "any_iterator.hpp"

class overloaded_constructor;
class member_function;
class static_member_function;

class class_type : public user_defined_type
{
public:
	constexpr virtual const overloaded_constructor& get_constructors() const noexcept = 0;
	constexpr virtual PP::any_view<const member_function&> get_member_functions() const noexcept = 0;
	constexpr virtual PP::any_view<const static_member_function&> get_static_member_functions() const noexcept = 0;

	constexpr virtual PP::any_view<const class_type&> get_nested_classes() const noexcept = 0;
};
