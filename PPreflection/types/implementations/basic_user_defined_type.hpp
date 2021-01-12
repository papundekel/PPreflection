#pragma once
#include <type_traits>
#include "basic_non_array_object_type.hpp"
#include "../user_defined_type.h"
#include "basic_named_type.hpp"
#include "../../parent_descriptor_reference.h"

namespace detail
{
	template <typename T, typename Base>
	class basic_user_defined_type : public basic_named_type<T, basic_non_array_object_type<T, Base>>
	{
		constexpr parent_descriptor_reference get_parent() const noexcept override final
		{
			return ::reflect(::reflect(PP::type_v<reflection::parent<T>>));
		}
	};
}
