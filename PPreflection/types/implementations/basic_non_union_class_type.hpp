#pragma once
#include "PP/concepts/non_union_class.hpp"

#include "../non_union_class_type.h"
#include "basic_class_type.hpp"

namespace PPreflection::detail
{
	template <typename T>
	class basic_non_union_class_type final : public basic_class_type<T, non_union_class_type>
	{
		static_assert(PP::concepts::non_union_class<T>);

		static constexpr auto base_classes = reflect_many(
			PP::type<const non_union_class_type&>,
			PPreflection::reflect(PP::type<tags::base_classes<T>>));

		constexpr PP::any_view<PP::iterator_category::ra, const non_union_class_type&> get_base_classes() const noexcept override final
		{
			return base_classes;
		}

		constexpr convertor_object base_pointer_conversion(const non_union_class_type&) const noexcept override final
		{
			return [](dynamic_reference){ return dynamic_object::create_void(); };
		}
		constexpr convertor_reference base_reference_conversion(const non_union_class_type&) const noexcept override final
		{
			return [](dynamic_reference r){ return r; };
		}
	};
}
