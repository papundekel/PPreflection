#pragma once
#include "../constructor.h"
#include "basic_overloaded_function.h"

namespace detail
{
	template <typename Class>
	using basic_overloaded_constructor_helper = basic_overloaded_function
		< reflection::constructors<Class>
		, constructor>;

	template <typename T>
	constexpr inline bool is_one_p_constructor = false;
	template <typename Class, typename Parameter>
	constexpr inline bool is_one_p_constructor<reflection::constructor<Class, Parameter>> =
		reflect(PP::type_v<reflection::is_explicit<Class, Parameter>>);

	template <typename Class>
	class basic_overloaded_constructor final : public basic_overloaded_constructor_helper<Class>
	{
		static constexpr auto& raw_overloads_ = basic_overloaded_constructor_helper<Class>::raw_overloads;

		static constexpr auto constructor_overloads = reflect_many(raw_overloads_, PP::type_v<const constructor&>);

		static constexpr auto one_parameter_converting_constructor_overloads =
			reflect_many(PP::tuple_filter<[](auto x) { return is_one_p_constructor<decltype(x)>; }>(raw_overloads_),
						 PP::type_v<const one_parameter_converting_constructor&>);

	public:
		constexpr PP::any_view<const constructor&> get_constructor_overloads() const noexcept override final
		{
			return constructor_overloads;
		}
		constexpr PP::any_view<const one_parameter_converting_constructor&> get_one_parameter_converting_constructor_overloads() const noexcept override final
		{
			return one_parameter_converting_constructor_overloads;
		}

		constexpr const class_type& get_parent() const noexcept override final
		{
			return type::reflect(PP::type_v<Class>);
		}
	};
}
