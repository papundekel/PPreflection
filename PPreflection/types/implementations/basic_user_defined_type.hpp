#pragma once
#include "../../basic_named_descriptor.h"
#include "../../parent_descriptor_reference.h"
#include "../user_defined_type.h"
#include "basic_non_array_object_type.hpp"

namespace PPreflection::detail
{
	namespace
	{
		template <typename T, typename Base>
		class basic_user_defined_type
			: public basic_named_descriptor<
				  T,
				  basic_non_array_object_type<T, Base>>
		{
			constexpr parent_descriptor_reference_strong get_parent(
				int) const noexcept override final
			{
				return PPreflection::reflect_descriptor(
					PPreflection::reflect(PP::type<tags::parent<T>>));
			}
		};
	}
}
