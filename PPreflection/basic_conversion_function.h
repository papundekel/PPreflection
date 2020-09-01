#pragma once
#include "ref_qualifier.h"
#include "cv_qualifier.h"
#include "conversion_function.h"
#include "basic_member_function.h"
#include <type_traits>

namespace detail
{
	template <typename Overload, bool Explicit, auto mf>
	class basic_conversion_function : public basic_member_function_base<Overload, mf, conversion_function>
	{
		using B = basic_member_function_base<Overload, mf, conversion_function>;
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
