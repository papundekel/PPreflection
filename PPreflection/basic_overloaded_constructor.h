#pragma once
#include "overloaded_constructor.h"
#include "basic_overloaded_function.h"
#include "constructor_info.h"
#include "map_pack.h"

namespace detail
{
	template <typename Class, typename Constructors>
	using basic_overloaded_constructor_helper = basic_overloaded_function<
		Class,
		map_pack_types<make_full_info<Class>::template make, Constructors>,
		overloaded_constructor>;

	template <typename Class, typename Constructors>
	class basic_overloaded_constructor : public basic_overloaded_constructor_helper<Class, Constructors>
	{
		using MappedConstructors = basic_overloaded_constructor_helper<Class, Constructors>::Functions;

	public:
		constexpr pointer_view<const cref_t<constructor>> get_constructor_overloads() const noexcept override final
		{
			return reflect_many<MappedConstructors, constructor>();
		}

		constexpr const type& get_enclosing_class() const noexcept override final
		{
			return reflect<Class, type>();
		}
	};
}
