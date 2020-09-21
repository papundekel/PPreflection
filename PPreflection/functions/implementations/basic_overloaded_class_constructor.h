#pragma once
#include "../constructor.h"
#include "basic_overloaded_function.h"
#include "map_pack.hpp"
#include "filter_pack.hpp"

namespace detail
{
	template <typename Class, typename Constructors>
	using basic_overloaded_class_constructor_helper = basic_overloaded_function<
		empty_id,
		PP::map_pack_types<make_full_info<Class>::template make, Constructors>,
		constructor>;

	template <typename Class, typename Constructors>
	class basic_overloaded_class_constructor final : public basic_overloaded_class_constructor_helper<Class, Constructors>
	{
		using MappedConstructors = basic_overloaded_class_constructor_helper<Class, Constructors>::Functions;
		using OneParameterConvertingConstructors = PP::filter_pack<is_one_p_conversion_info, MappedConstructors>;

	public:
		constexpr PP::any_view<const constructor&> get_constructor_overloads() const noexcept override final
		{
			return reflect_many<MappedConstructors, const constructor&>();
		}
		constexpr PP::any_view<const one_parameter_converting_constructor&> get_one_parameter_converting_constructor_overloads() const noexcept override final
		{
			return reflect_many<OneParameterConvertingConstructors, const one_parameter_converting_constructor&>();
		}

		constexpr const class_type& get_parent() const noexcept override final
		{
			return type::reflect<Class>();
		}
	};
}
