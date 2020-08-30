#pragma once
#include "member_function.h"

class conversion_function : public member_function
{
protected:
	constexpr virtual void invoke_implementation_conversion(void* result, const dynamic_reference& caller) const noexcept = 0;

	constexpr void invoke_implementation_member(void* result, const dynamic_reference& caller, const dynamic_reference* args) const noexcept override final;
public:
	constexpr dynamic_object invoke_unsafe(const dynamic_reference& caller) const noexcept;
	constexpr dynamic_object invoke(const dynamic_reference& caller) const;
};
