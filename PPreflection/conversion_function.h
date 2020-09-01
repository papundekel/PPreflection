#pragma once
#include "member_function.h"
#include "overloaded_conversion_function.h"

class conversion_function : public member_function
{
	friend class overloaded_conversion_function;

protected:
	constexpr virtual void invoke_implementation_conversion(void* result, dynamic_reference caller) const noexcept = 0;

	constexpr void invoke_implementation_member(void* result, dynamic_reference caller, const dynamic_reference* args) const noexcept override final
	{
		invoke_implementation_conversion(result, caller);
	}
public:
	constexpr const overloaded_conversion_function& get_overloaded_function() const noexcept override = 0;

	constexpr virtual bool is_explicit() const noexcept = 0;

	constexpr dynamic_object invoke_unsafe(dynamic_reference caller) const noexcept
	{
		return dynamic_object(return_type(),
			[this, caller](void* ptr)
			{
				invoke_implementation_conversion(ptr, caller);
			});
	}
	constexpr dynamic_object invoke(dynamic_reference caller) const
	{
		if (can_invoke(caller))
			return invoke_unsafe(caller);
		else
			throw 0;
	}
};
