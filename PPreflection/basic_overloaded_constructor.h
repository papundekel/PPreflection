#pragma once
#include "overloaded_constructor.h"
#include "basic_overloaded_function.h"
#include "constructor_info.h"
#include "map_pack.h"
#include "filter_pack.h"

namespace detail
{
	template <typename Class, typename Constructors>
	using basic_overloaded_constructor_helper = basic_overloaded_function<
		empty_id,
		map_pack_types<make_full_info<Class>::template make, Constructors>,
		overloaded_constructor>;

	template <typename Class, typename Constructors>
	class basic_overloaded_constructor final : public basic_overloaded_constructor_helper<Class, Constructors>
	{
		using MappedConstructors = basic_overloaded_constructor_helper<Class, Constructors>::Functions;
		using OneParameterConvertingConstructors = filter_pack<is_one_p_conversion_info, MappedConstructors>;

	public:
		constexpr pointer_view<const cref_t<constructor>> get_constructor_overloads() const noexcept override final
		{
			return reflect_many<MappedConstructors, constructor>();
		}
		constexpr pointer_view<const cref_t<one_parameter_converting_constructor>> get_one_parameter_converting_constructor_overloads() const noexcept override final
		{
			return reflect_many<OneParameterConvertingConstructors, one_parameter_converting_constructor>();
		}

		constexpr const type& get_enclosing_class() const noexcept override final
		{
			return reflect<Class, type>();
		}
	};
}
