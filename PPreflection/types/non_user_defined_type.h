#pragma once
#include "../descriptor.h"

namespace PPreflection
{
	namespace detail
	{
		template <typename Base>
		class non_user_defined_type : public Base
		{
			constexpr const descriptor& get_parent() const noexcept override final
			{
				return *this;
			}
		};
	}
}
