#pragma once
#include "../parent_descriptor_reference.h"
#include "dynamic_cv_qualifiable_type.h"
#include "dynamic_named_descriptor.h"
#include "user_defined_type.h"

namespace PPreflection
{
	namespace detail
	{
		template <typename Base>
		class dynamic_user_defined_type : public detail::dynamic_named_descriptor<detail::dynamic_cv_qualifiable_type<Base>>
		{
			static_assert(PP::concepts::derived_from<Base, user_defined_type>);

			parent_descriptor_reference parent;

		public:
			constexpr dynamic_user_defined_type(PP::string_view name, parent_descriptor_reference parent, PP::cv_qualifier cv = PP::cv_qualifier::none) noexcept
				: dynamic_named_descriptor<dynamic_cv_qualifiable_type<Base>>(name, cv)
				, parent(parent)
			{}

			constexpr parent_descriptor_reference get_parent(int = 0) const noexcept override final
			{
				return parent;
			}
		};
	}
}
