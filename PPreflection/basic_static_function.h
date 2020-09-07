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
		using B = basic_static_function_base<Overload, f, Base>;
		using ReturnType = typename B::ReturnType;
		using ParameterTypes = typename B::ParameterTypes;

		constexpr dynamic_object invoke_unsafe(any_iterator<const dynamic_reference&> arg_iterator) const noexcept override final
		{
			return invoke_helper<ReturnType, ParameterTypes>(f, arg_iterator);
		}
	};
}
