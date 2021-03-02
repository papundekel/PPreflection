#pragma once
#include "PP/decompose_template.hpp"
#include "PP/tuple_filter.hpp"
#include "PP/type_to_value.hpp"

#include "../constructor.h"
#include "basic_overloaded_function.h"

namespace PPreflection::detail
{
	template <typename Class>
	class basic_overloaded_constructor final
		: public basic_overloaded_function<PPreflection::tags::constructors<Class>, constructor>
	{
		static constexpr auto constructor_overloads = reflect_many(PP::type<const constructor&>, basic_overloaded_constructor::raw_overloads);

		static constexpr auto one_parameter_converting_constructor_overloads =
			reflect_many(PP::type<const one_parameter_converting_constructor&>,
				PP::tuple_filter([]
					(PP::concepts::type auto t)
					{
						constexpr auto decomposition = *t;
						constexpr auto types = decomposition.types;

						return PP::value<decomposition.Template == PP::Template<tags::constructor> && PP::tuple_count(types) == 2> &&
							!reflect(PP::Template<tags::is_explicit>[types]);
					}, basic_overloaded_constructor::raw_overloads));

		constexpr PP::any_view<PP::iterator_category::ra, const constructor&> get_constructor_overloads() const noexcept override final
		{
			return constructor_overloads;
		}
		constexpr PP::any_view<PP::iterator_category::ra, const one_parameter_converting_constructor&> get_one_parameter_converting_constructor_overloads() const noexcept override final
		{
			return one_parameter_converting_constructor_overloads;
		}

		constexpr const class_type& get_parent() const noexcept override final
		{
			return type::reflect(PP::type<Class>);
		}
	};
}
