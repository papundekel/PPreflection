#pragma once
#include "PP/remove_extent.hpp"

#include "../complete_object_type.h"
#include "basic_object_type.hpp"

namespace PPreflection::detail
{
	template <typename T, typename Base>
	class basic_array_type : public Base
	{
	public:
		constexpr cv_type<complete_object_type> remove_extent() const noexcept
		{
			return type::reflect_cv | PP::remove_extent <<= PP::type<T>;
		}

		constexpr convertor array_to_pointer_conversion() const noexcept override final
		{
			return create_convertor_to_value(PP::type<T>);
		}
	};
}
