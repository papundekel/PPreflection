#pragma once
#include "basic_class_constructor.h"

template <typename Class, typename Args, bool Noexcept>
constexpr void detail::basic_class_constructor<Class, Args, Noexcept>::invoke_implementation(void* result, const dynamic_reference* args) const noexcept
{
	new (result) Class(get_value<apply_pack<function::invoke_helper_t, Args>>()(
		[]<typename... T>(T&&... xs)
		{
			return Class(std::forward<T>(xs)...);
		}, args));
}
