#pragma once
#include "../non_union_class_type.h"
#include "basic_class_type.hpp"
#include "concepts/non_union_class.hpp"

namespace PPreflection::detail
{
	template <typename T>
	class basic_non_union_class_type final : public basic_class_type<T, non_union_class_type>
	{
		static_assert(PP::concepts::non_union_class<T>);

		static constexpr auto base_classes =
			reflect_many(PPreflection::reflect(PP::type<tags::base_classes<T>>), PP::type<const non_union_class_type&>);

		constexpr PP::any_view<PP::iterator_category::ra, const non_union_class_type&> get_base_classes() const noexcept override final
		{
			return base_classes;
		}
	};
}
