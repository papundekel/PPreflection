#pragma once
#include "basic_function.h"
#include "get_function_info.h"

namespace detail
{
	template <typename Overload, typename F, typename Base>
	using basic_typed_function_base = basic_function<
		Overload,
		typename get_function_info<F>::parameter_types,
		typename get_function_info<F>::return_type,
		get_function_info<F>::Noexcept,
		Base>;

	template <typename Overload, typename F, typename Base>
	class basic_typed_function : public basic_typed_function_base<Overload, F, Base>
	{
	protected:
		using FunctionType = F;
		using B = basic_typed_function_base<Overload, F, Base>;
	};
}
