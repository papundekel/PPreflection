#pragma once
#include "non_array_object_type.h"

namespace PPreflection
{
	class pointer_to_member_type;
	class pointer_type;
	class null_type;

	namespace detail
	{
		class pointer_base_type
		{
			friend pointer_to_member_type;
			friend pointer_type;
			friend null_type;

			class wrapped : public non_array_object_type
			{
				friend pointer_to_member_type;
				friend pointer_type;
				friend null_type;

				constexpr virtual convertor_object bool_conversion()
					const noexcept = 0;

				constexpr virtual convertor_object null_pointer_conversion()
					const noexcept = 0;
			};
		};
	}
}
