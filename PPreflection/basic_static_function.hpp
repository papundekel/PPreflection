#pragma once
#include <type_traits>
#include "basic_static_function.h"

template <typename Overload, auto f, typename Base>
constexpr void detail::basic_static_function<Overload, f, Base>::invoke_implementation(void* result, const dynamic_ptr* args) const noexcept
{
	this->invoke_(result,
		[args]()
		{
			return get_value<apply_pack<function::invoke_helper_t, ParameterTypes>>()(f, args);
		});
}
