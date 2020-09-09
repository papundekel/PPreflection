#pragma once
#include "overloaded_constructor.h"
#include "basic_overloaded_function.h"
#include "constructor_info.h"
#include "../PP/PP/map_pack.hpp"
#include "../PP/PP/filter_pack.hpp"

namespace detail
{
	template <typename Class, typename Constructors>
	using basic_overloaded_class_constructor_helper = basic_overloaded_function<
		empty_id,
		PP::map_pack_types<make_full_info<Class>::template make, Constructors>,
		overloaded_constructor>;

	template <typename Class, typename Constructors>
	class basic_overloaded_class_constructor final : public basic_overloaded_class_constructor_helper<Class, Constructors>
	{
		using MappedConstructors = basic_overloaded_class_constructor_helper<Class, Constructors>::Functions;
		using OneParameterConvertingConstructors = PP::filter_pack<is_one_p_conversion_info, MappedConstructors>;

	public:
		constexpr any_view<const constructor&> get_constructor_overloads() const noexcept override final
		{
			return reflect_many<MappedConstructors, constructor>();
		}
		constexpr any_view<const one_parameter_converting_constructor&> get_one_parameter_converting_constructor_overloads() const noexcept override final
		{
			return reflect_many<OneParameterConvertingConstructors, one_parameter_converting_constructor>();
		}

		constexpr const type& get_parent() const noexcept override final
		{
			return reflect<Class, type>();
		}
	};
}
