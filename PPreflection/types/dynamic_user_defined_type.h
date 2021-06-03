#pragma once
#include "../parent_descriptor_reference_strong.h"
#include "dynamic_named_descriptor.h"
#include "user_defined_type.h"

namespace PPreflection
{
	namespace detail
	{
		template <typename Base>
		class dynamic_user_defined_type : public dynamic_named_descriptor<Base>
		{
			static_assert(PP::concepts::derived_from<Base, user_defined_type>);

			parent_descriptor_reference_strong parent;

		public:
			constexpr dynamic_user_defined_type(
				PP::string_view name,
				parent_descriptor_reference_strong parent) noexcept
				: dynamic_named_descriptor<Base>(name)
				, parent(parent)
			{}

			constexpr parent_descriptor_reference_strong get_parent(
				int) const noexcept override final
			{
				return parent;
			}
		};
	}
}
