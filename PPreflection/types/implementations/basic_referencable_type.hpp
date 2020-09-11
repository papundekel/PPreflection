#pragma once
#include <type_traits>
#include "../referencable_type.h"

namespace detail
{
	template <typename T, typename Base>
	class basic_referencable_type : public Base
	{
		constexpr const reference_type& make_lreference() const noexcept override final
		{
			return type::reflect<T&>();
		}
		constexpr const reference_type& make_rreference() const noexcept override final
		{
			return type::reflect<T&&>();
		}
	};
}
