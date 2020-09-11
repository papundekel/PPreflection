#pragma once
#include "basic_type.hpp"
#include "../pointable_type.h"

namespace detail
{
	template <typename T, typename Base>
	class basic_pointable_type : public basic_type<T, Base>
	{
		constexpr const pointer_type& make_pointer() const noexcept override final
		{
			return type::reflect<T*>();
		}
	};
}
