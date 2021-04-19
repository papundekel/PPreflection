#pragma once
#include "cv_type.h"
#include "reference_type.h"

namespace PPreflection
{
	namespace detail
	{
		class dynamic_specific_reference_type_base : public reference_type
		{
			cv_type<referencable_type> referenced_type;

		public:
			constexpr dynamic_specific_reference_type_base(cv_type<referencable_type> referenced_type) noexcept
				: referenced_type(referenced_type)
			{}

			constexpr cv_type<referencable_type> remove_reference() const noexcept override final
			{
				return referenced_type;
			}
		};
	}
}
