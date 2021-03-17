#pragma once
#include "pointer_type.h"

namespace PPreflection
{
	class dynamic_pointer_type final : public pointer_type
	{
		cv_type<pointable_type> pointed_to_type;

	public:
		constexpr explicit dynamic_pointer_type(cv_type<pointable_type> pointed_to_type) noexcept
			: pointed_to_type(pointed_to_type)
		{}

		constexpr virtual cv_type<pointable_type> remove_pointer() const noexcept override final
		{
			return pointed_to_type;
		}
		constexpr convertor_object function_pointer_conversion() const noexcept override final
		{
			return nullptr;
		}
	};
}
