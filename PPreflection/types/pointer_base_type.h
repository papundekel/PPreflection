#pragma once
#include "non_array_object_type.h"

namespace PPreflection
{
	class pointer_base_type : public non_array_object_type
	{
	public:
		constexpr virtual convertor_object bool_conversion() const noexcept = 0;

		constexpr virtual convertor_object null_pointer_conversion()
			const noexcept = 0;
	};
}
