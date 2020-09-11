#pragma once
#include <type_traits>
#include "basic_non_member_function_type.hpp"
#include "../function_type.h"

namespace detail
{
	template <typename T>
	class basic_function_type final : public basic_non_member_function_type_base<T, function_type>
	{
		constexpr PP::cv_qualifier get_cv_qualifier() const noexcept override final
		{
			return PP::get_function_info<T>::cv;
		}
		constexpr PP::ref_qualifier get_ref_qualifier() const noexcept override final
		{
			return PP::get_function_info<T>::ref;
		}
	};
}
