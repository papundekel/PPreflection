#pragma once
#include "basic_function.h"
#include "member_like_function.h"

namespace detail
{
	template <typename Class, typename Args, bool Noexcept>
	class basic_class_constructor : public basic_function<Class, Args, Class, Noexcept, member_like_function>
	{
	protected:
		constexpr void invoke_implementation(void* result, const dynamic_ptr* args) const noexcept override final;
	};
}
