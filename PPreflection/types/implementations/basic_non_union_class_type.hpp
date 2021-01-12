#pragma once
#include <type_traits>
#include "basic_class_type.hpp"
#include "../non_union_class_type.h"

namespace detail
{
	template <typename T>
	class basic_non_union_class_type final : public basic_class_type<T, non_union_class_type>
	{
		static_assert(std::is_class_v<T>);

		static constexpr auto base_classes =
			reflect_many(::reflect(PP::type_v<reflection::base_classes<T>>), PP::type_v<const non_union_class_type&>);

		constexpr PP::any_view<const non_union_class_type&> get_base_classes() const noexcept override final
		{
			return base_classes;
		}
	};
}
