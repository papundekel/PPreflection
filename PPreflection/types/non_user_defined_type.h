#pragma once
#include "../descriptor.h"

namespace detail
{
	template <typename Base>
	class non_user_defined_type : public Base
	{
		constexpr const descriptor* get_parent_implementation() const noexcept override final
		{
			return nullptr;
		}
	};
}