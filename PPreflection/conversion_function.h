#pragma once
#include "member_function.h"

class conversion_function : public member_function
{
protected:
	constexpr virtual void invoke_implementation_conversion(void* result, const dynamic_reference& caller) const noexcept = 0;

	constexpr void invoke_implementation_member(void* result, const dynamic_reference& caller, const dynamic_reference* args) const noexcept override final
	{
		invoke_implementation_conversion(result, caller);
	}
public:
	constexpr dynamic_object invoke_unsafe(const dynamic_reference& caller) const noexcept
	{
		return dynamic_object(return_type(),
			[this, &caller](void* ptr)
			{
				invoke_implementation_conversion(ptr, caller);
			});
	}
	constexpr dynamic_object invoke(const dynamic_reference& caller) const
	{
		if (can_invoke(caller))
			return invoke_unsafe(caller);
		else
			throw 0;
	}
};
