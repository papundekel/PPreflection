#pragma once
#include <type_traits>
#include "ref_qualifier.h"
#include "cv_qualifier.h"
#include "conversion_function.h"
#include "basic_member_function.h"
#include "overload_cast.h"
#include "conversion_function_info.h"
#include "get_member_function_info.h"

namespace detail
{
	template <auto mf>
	using basic_conversion_function_helper =
		basic_member_function_base
			< overloaded_conversion_function_info<
				typename get_member_function_info<decltype(mf)>::Class,
				typename get_function_info<typename get_member_function_info<decltype(mf)>::Function>::return_type>
			, mf
			, conversion_function>;

	template <auto mf, bool Explicit>
	class basic_conversion_function
		: public basic_conversion_function_helper<mf>
	{
		using B = basic_conversion_function_helper<mf>;
		using CallerParameterType = B::CallerParameterType;

	protected:
		constexpr void invoke_implementation_conversion(void* result, dynamic_reference caller) const noexcept override final
		{
			this->invoke_(result,
				[caller]() -> decltype(auto)
				{
					return (caller.cast_unsafe<CallerParameterType>().*mf)();
				});
		}
		constexpr bool is_explicit() const noexcept override final
		{
			return Explicit;
		}
	};
}
