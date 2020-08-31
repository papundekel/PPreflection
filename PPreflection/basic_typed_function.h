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

		template <typename T>
		static constexpr void invoke_(void* result, T&& t) noexcept
		{
			using R = B::ReturnType;

			if constexpr (!std::is_void_v<R>)
			{
				if constexpr (!std::is_reference_v<R>)
					new (result) R(std::forward<T>(t)());
				else
				{
					auto&& x = std::forward<T>(t)();
					new (result) std::remove_reference_t<R>*(&x);
				}
			}
			else
				std::forward<T>(t)();
		}

	};
}