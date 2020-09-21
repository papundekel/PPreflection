#pragma once
#include <type_traits>
#include "basic_class_type.hpp"
#include "../non_union_class_type.h"

namespace detail
{
	template <typename T, typename MemberFunctions, typename StaticMemberFunctions, typename NestedClasses, typename BaseClasses>
	class basic_non_union_class_type final : public basic_class_type<T, non_union_class_type>
	{
		static_assert(std::is_class_v<T>);

		constexpr PP::any_view<const non_union_class_type&> get_base_classes() const noexcept override final
		{
			return ::reflect<base_classes<T>, const non_union_class_type&>();
		}
	};
}
