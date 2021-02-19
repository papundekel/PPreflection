#pragma once
#include "../constructor.h"
#include "basic_overloaded_function.h"
#include "tuple_filter.hpp"
#include "type_to_value.hpp"

namespace PPreflection::detail
{
	template <typename Class>
	using basic_overloaded_constructor_helper = basic_overloaded_function<
		tags::constructors<Class>,
		constructor>;

	template <typename Class>
	class basic_overloaded_constructor final : public basic_overloaded_constructor_helper<Class>
	{
		static constexpr auto constructor_overloads = reflect_many(basic_overloaded_constructor::raw_overloads, PP::type<const constructor&>);

		static constexpr auto one_parameter_converting_constructor_overloads =
			reflect_many(
				PP::tuple_filter([]
					(PP::concepts::type auto x)
					{
						return PP::value<x->Template == PP::Template<>>;
					}, basic_overloaded_constructor::raw_overloads),
				PP::type<const one_parameter_converting_constructor&>);

	public:
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
