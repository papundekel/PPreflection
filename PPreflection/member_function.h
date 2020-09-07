#pragma once
#include <utility>
#include "maybe_static_member_function.h"
#include "type.h"
#include "overloaded_member_function.h"

class member_function : public detail::maybe_static_member_function
{
	friend class overloaded_member_function;
	friend class overloaded_conversion_function;

	constexpr virtual dynamic_object invoke_unsafe_member(dynamic_reference caller, any_iterator<const dynamic_reference&> arg_iterator) const = 0;

protected:
	constexpr bool can_invoke(const type& caller_arg_type) const noexcept;

	constexpr dynamic_object invoke_unsafe(any_iterator<const dynamic_reference&> arg_iterator) const noexcept override final;
	constexpr bool can_invoke(any_view<const type&> argument_types) const noexcept override final;

	constexpr virtual const type& get_pointer_type() const noexcept = 0;

	constexpr virtual const type& get_caller_parameter_type() const noexcept = 0;

public:
	constexpr void print_name(simple_ostream& out) const noexcept override final;
	constexpr bool has_name(std::string_view name) const noexcept override final;

	constexpr const overloaded_member_function& get_overloaded_function() const noexcept override = 0;
		
	constexpr virtual ref_qualifier get_ref_qualifier() const noexcept = 0;
	constexpr virtual cv_qualifier get_cv_qualifier() const noexcept = 0;

	constexpr dynamic_object invoke(dynamic_reference caller, pointer_view<const dynamic_reference> args = {}) const;
};
