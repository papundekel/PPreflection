#pragma once
#include "PP/concepts/non_union_class.hpp"
#include "PP/construct_pack.hpp"
#include "PP/copy_cvref.hpp"
#include "PP/tuple_concat.hpp"
#include "PP/tuple_map_to_array.hpp"
#include "PP/zip_view.hpp"

#include "../non_union_class_type.h"
#include "basic_class_type.hpp"

namespace PPreflection::detail
{
	constexpr auto get_base_classes_impl(PP::concepts::type auto t) noexcept
	{
		auto base_classes_direct = PPreflection::reflect(PP::Template<tags::base_classes>(t));

		return !PP::tuple_concats(base_classes_direct += PP::tuple_map([](PP::concepts::type auto u) { return get_base_classes_impl(u); }, base_classes_direct));
	}

	template <typename T>
	class basic_non_union_class_type final : public basic_class_type<T, non_union_class_type>
	{
		static_assert(PP::concepts::non_union_class<T>);

		static constexpr auto base_classes_direct = PPreflection::reflect(PP::type<tags::base_classes<T>>);

		static constexpr auto base_classes_direct_dynamic = reflect_many(PP::type<const non_union_class_type&>, base_classes_direct);

		static constexpr auto base_classes = get_base_classes_impl(PP::type<T>);

		static constexpr auto base_classes_dynamic = reflect_many(PP::type<const non_union_class_type&>, base_classes);

		static constexpr auto base_class_reference_convertors = PP::tuple_map_to_array(PP::type<convertor_reference>, []
			(PP::concepts::type auto base_class_type)
			{
				return create_convertor_reference(PP::type<T>, PP::value<[]
					(auto&& derived_r) -> auto&&
					{
						return PP::copy_cvref(PP_DECLTYPE(derived_r), PP_COPY_TYPE(base_class_type))(derived_r);
					}>);
			}, base_classes);

		constexpr PP::any_view<PP::iterator_category::ra, const non_union_class_type&> get_base_classes() const noexcept override final
		{
			return base_classes_dynamic;
		}

		constexpr convertor_object base_pointer_conversion(const non_union_class_type&) const noexcept override final
		{
			return [](dynamic_reference r){ return dynamic_object::create_shallow_copy(r); };
		}

		constexpr convertor_reference base_reference_conversion(const non_union_class_type& base_target) const noexcept override final
		{
			auto classes_convertors = PP::zip_view_pack(base_classes_dynamic, base_class_reference_convertors);

			auto i = PP::view_find(*PP::functor([&base_target]
				(const auto& base, auto&&)
				{
					return base == base_target;
				}), classes_convertors);

			if (i != classes_convertors.end())
				return (*i)[PP::value_1];
			else
				return [](dynamic_reference r){ return r; };
		}
	};
}
