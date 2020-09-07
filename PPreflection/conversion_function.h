#pragma once
#include "member_function.h"
#include "overloaded_conversion_function.h"

class conversion_function : public member_function
{
	friend class overloaded_conversion_function;

protected:
	constexpr virtual dynamic_object invoke_unsafe_conversion(dynamic_reference caller) const noexcept = 0;

	constexpr dynamic_object invoke_unsafe_member(dynamic_reference caller, any_iterator<const dynamic_reference&>) const noexcept override final
	{
		return invoke_unsafe_conversion(caller);
	}
public:
	constexpr const overloaded_conversion_function& get_overloaded_function() const noexcept override = 0;

	constexpr virtual bool is_explicit() const noexcept = 0;

	constexpr dynamic_object invoke(dynamic_reference caller) const
	{
		if (can_invoke(caller.get_type()))
			return invoke_unsafe_conversion(caller);
		else
			return dynamic_object::create_invalid();
	}
};
