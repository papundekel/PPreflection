#pragma once
#include "PP/concepts/derived_from.hpp"

#include "../descriptor.h"

namespace PPreflection
{
	namespace detail
	{
		template <typename Base>
		class non_user_defined_type : public Base
		{
			static_assert(PP::concepts::derived_from<Base, descriptor>);

		public:
			constexpr parent_descriptor_reference get_parent(
				void* = nullptr) const noexcept override final;
		};
	}
}
