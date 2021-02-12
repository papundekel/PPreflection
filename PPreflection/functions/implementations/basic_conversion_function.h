#pragma once
#include "../../overload_cast.h"
#include "../conversion_function.h"
#include "apply_template.hpp"
#include "basic_member_function.h"
#include "empty_tuple.hpp"

namespace PPreflection::detail
{
	template <auto mf>
	class basic_conversion_function
		: public basic_member_function_base<mf, conversion_function>
	{
		dynamic_variable invoke_unsafe_conversion(dynamic_reference caller) const noexcept override final
		{
			return invoke_helper(
				[this, caller]() -> decltype(auto)
				{
					return (caller.cast_unsafe(this->caller_type).*mf)();
				}, {}, PP::empty_tuple{});
		}
		constexpr bool is_explicit() const noexcept override final
		{
			return reflect(PP::Template<tags::is_explicit>(PP::type<PP::value_t<mf>>));
		}
	};
}
