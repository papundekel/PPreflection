#pragma once
#include "PP/concepts/class.hpp"
#include "PP/concepts/derived_from.hpp"
#include "PP/concepts/destructible.hpp"
#include "PP/destroy_at.hpp"
#include "PP/tuple_filter.hpp"
#include "PP/tuple_map.hpp"
#include "PP/tuple_prepend.hpp"
#include "PP/tuple_to_array.hpp"

#include "../../functions/constructor.h"
#include "../../functions/member_function.h"
#include "../../functions/static_member_function.h"
#include "../../reflect.h"
#include "../class_type.h"
#include "basic_user_defined_type.hpp"

namespace PPreflection::detail
{
	template <typename T, typename Base>
	class basic_class_type : public basic_user_defined_type<T, Base>
	{
		static_assert(PP::concepts::derived_from<Base, class_type>);
		static_assert(PP::concepts::class_type<T>);

		static constexpr auto reflector = reflect_many_helper * PP::type<T>;

		static constexpr auto static_member_functions = reflector(PP::Template<tags::static_member_functions>, PP::type<const static_member_function&>);
		static constexpr auto member_functions = reflector(PP::Template<tags::member_functions>, PP::type<const member_function&>);
		static constexpr auto nested_types = reflector(PP::Template<tags::nested_types>, PP::type<const user_defined_type&>);

		static constexpr auto constructors = reflect_many(PP::type<const constructor&>,
			PP::functor([]
				(PP::concepts::tuple auto constructor_parameter_types)
				{
					return PP::Template<tags::constructor>[PP::type<T> += constructor_parameter_types];
				}) + PPreflection::reflect(PP::type<tags::constructors<T>>));

		static constexpr auto conversion_functions = PP::type<const conversion_function&> & PP::tuple_filter([]
			<typename F>
			(const F& f)
			{
				return PP::value<PP::concepts::derived_from<F, conversion_function>>;
			}, PPreflection::reflect + PPreflection::reflect(PP::type<tags::member_functions<T>>));

	public:
		void destroy(void* ptr) const noexcept override final
		{
			if constexpr (PP::concepts::destructible<T>)
				PP::destroy_at(reinterpret_cast<T*>(ptr));
		}

		constexpr PP::any_view<PP::iterator_category::ra, const constructor&> get_constructors() const noexcept override final
		{
			return constructors;
		}
		constexpr PP::any_view<PP::iterator_category::ra, const member_function&> get_member_functions() const noexcept override final
		{
			return member_functions;
		}
		constexpr PP::any_view<PP::iterator_category::ra, const conversion_function&> get_conversion_functions() const noexcept override final
		{
			return conversion_functions;
		}
		constexpr PP::any_view<PP::iterator_category::ra, const static_member_function&> get_static_member_functions() const noexcept override final
		{
			return static_member_functions;
		}
		constexpr PP::any_view<PP::iterator_category::ra, const user_defined_type&> get_nested_types() const noexcept override final
		{
			return nested_types;
		}
	};
}
