#pragma once
#include "PP/concepts/class.hpp"
#include "PP/concepts/derived_from.hpp"
#include "PP/concepts/destructible.hpp"
#include "PP/destroy_at.hpp"
#include "PP/tuple_filter.hpp"

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

		static constexpr auto static_member_functions = reflector(PP::Template<tags::static_member_functions>, PP::type<const static_member_function::overloaded&>);
		static constexpr auto member_functions = reflector(PP::Template<tags::member_functions>, PP::type<const member_function::overloaded&>);
		static constexpr auto nested_classes = reflector(PP::Template<tags::nested_classes>, PP::type<const user_defined_type&>);

		static constexpr auto conversion_functions = reflect_many(PP::type<const conversion_function::overloaded&>,
			PP::tuple_filter([]
				(PP::concepts::type auto t)
				{
					return PP::value<PP_COPY_TYPE(t)->Template == PP::Template<tags::conversion_function>>;
				}, PPreflection::reflect(PP::type<tags::member_functions<T>>)));

	public:
		void destroy(void* ptr) const noexcept override final
		{
			if constexpr (PP::concepts::destructible<T>)
				PP::destroy_at(reinterpret_cast<T*>(ptr));
		}

		constexpr const constructor::overloaded& get_constructors() const noexcept override final
		{
			return reflect(PP::type<tags::constructors<T>>);
		}
		constexpr PP::any_view<PP::iterator_category::ra, const member_function::overloaded&> get_member_functions() const noexcept override final
		{
			return member_functions;
		}
		constexpr PP::any_view<PP::iterator_category::ra, const conversion_function::overloaded&> get_conversion_functions() const noexcept override final
		{
			return conversion_functions;
		}
		constexpr PP::any_view<PP::iterator_category::ra, const static_member_function::overloaded&> get_static_member_functions() const noexcept override final
		{
			return static_member_functions;
		}
		constexpr PP::any_view<PP::iterator_category::ra, const user_defined_type&> get_nested_classes() const noexcept override final
		{
			return nested_classes;
		}
	};
}
