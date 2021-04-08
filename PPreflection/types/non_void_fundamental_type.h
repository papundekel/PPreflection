#pragma once
#include "named_type.h"
#include "non_array_object_type.h"
#include "non_user_defined_type.h"

namespace PPreflection
{
	class dynamic_object;

	class non_void_fundamental_type : public detail::named_type<detail::non_user_defined_type<non_array_object_type>>
	{
	public:
		constexpr PP::variant<
			const non_void_fundamental_type&,
			const pointer_type&,
			const pointer_to_member_type&,
			const user_defined_type&> cast_down(PP::overload_tag<non_array_object_type>) const noexcept override final
		{
			return {PP::placeholder, *this};
		}

		constexpr void destroy(void*) const noexcept override final
		{}

		virtual dynamic_object create_instance() const noexcept = 0;
	};
}
