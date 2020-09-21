#pragma once
#include <type_traits>
#include "basic_member_function.h"
#include "../conversion_function.h"
#include "../../overload_cast.h"
#include "get_member_function_info.hpp"

namespace detail
{
	template <auto mf>
	using basic_conversion_function_helper =
		basic_member_function_base
			< overloaded_conversion_function_info<
				typename PP::get_member_function_info<decltype(mf)>::Class,
				typename PP::get_function_info<typename PP::get_member_function_info<decltype(mf)>::Function>::return_type>
			, mf
			, conversion_function>;

	template <auto mf, bool Explicit>
	class basic_conversion_function
		: public basic_conversion_function_helper<mf>
	{
		using B = basic_conversion_function_helper<mf>;
		using Caller = typename B::Caller;
		using ReturnType = typename B::ReturnType;

	protected:
		inline dynamic_variable invoke_unsafe_conversion(dynamic_reference caller) const noexcept override final
		{
			return invoke_helper<ReturnType>([caller]() -> decltype(auto) { return (caller.cast_unsafe<Caller>().*mf)(); });
		}
		constexpr bool is_explicit() const noexcept override final
		{
			return Explicit;
		}
	};
}
