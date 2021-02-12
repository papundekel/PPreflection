#pragma once
#include "complete_object_type.h"

namespace PPreflection
{
	template <typename Base>
	class dynamic_array_type : public Base
	{
		const complete_object_type& inner_type;

	public:
		constexpr explicit dynamic_array_type(const complete_object_type& inner_type) noexcept
			: inner_type(inner_type)
		{}

		constexpr const complete_object_type& remove_extent() const noexcept override final
		{
			return inner_type;
		}
	};
}
