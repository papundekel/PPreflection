#pragma once
#include <type_traits>
#include "basic_typed_function.h"

namespace detail
{
	template <typename Overload, auto f, typename Base>
	using basic_static_function_base = basic_typed_function<Overload, std::remove_pointer_t<decltype(f)>, Base>;

	template <typename Overload, auto f, typename Base>
	class basic_static_function : public basic_static_function_base<Overload, f, Base>
	{
	protected:
		using ParameterTypes = typename basic_static_function_base<Overload, f, Base>::ParameterTypes;

		constexpr void invoke_implementation(void* result, const dynamic_reference* args) const noexcept override final
		{
			this->invoke_(result,
				[args]() -> decltype(auto)
				{
					return get_value<apply_pack<function::invoke_helper_t, ParameterTypes>>()(f, args);
				});
		}

	};
}
