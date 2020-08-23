#pragma once
#include <utility>
#include "member_like_function.h"
#include "type.h"
#include "overloaded_member_function.h"

class member_function : public member_like_function_base
{
	friend class overloaded_member_function;

	constexpr dynamic_object invoke_unsafe(const dynamic_reference& caller, simple_range<const dynamic_reference> args) const;

protected:
	constexpr bool can_invoke(const dynamic_reference& caller) const noexcept;

	constexpr virtual void invoke_implementation_member(void* result, const dynamic_reference& caller, const dynamic_reference* args) const noexcept = 0;

	constexpr void invoke_implementation(void* result, const dynamic_reference* args) const noexcept override final;
	constexpr bool can_invoke(simple_range<const dynamic_reference> args) const noexcept override final;

	constexpr virtual const type& get_pointer_type() const noexcept = 0;

	constexpr virtual const type& get_caller_parameter_type() const noexcept = 0;

public:
	constexpr virtual const overloaded_member_function& get_overloaded_function() const noexcept = 0;
		
	constexpr virtual ref_qualifier get_ref_qualifier() const noexcept = 0;
	constexpr virtual cv_qualifier get_cv_qualifier() const noexcept = 0;

	constexpr dynamic_object invoke(const dynamic_reference& caller, simple_range<const dynamic_reference> args = {}) const;
};
