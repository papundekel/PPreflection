#pragma once
#include "reference_type.h"

namespace PPreflection
{
	namespace detail
	{
		class dynamic_specific_reference_type_base : public reference_type
		{
			const referencable_type& referenced_type;

		public:
			constexpr dynamic_specific_reference_type_base(const referencable_type& referenced_type) noexcept
				: referenced_type(referenced_type)
			{}

			constexpr const referencable_type& remove_reference() const noexcept override final
			{
				return referenced_type;
			}
		};
	}
}
