#pragma once
#include "basic_overloaded_member_function.h"
#include "../conversion_function.h"
#include "map_pack.hpp"
#include "../../types/types.h"

namespace detail
{
	template <typename ID, typename Functions>
	using basic_overloaded_conversion_function_helper = basic_overloaded_member_function_base
		< empty_id
		, PP::map_pack_types<make_conversion_function<typename ID::Class, typename ID::Result>::template make, Functions>
		, conversion_function>;

	template <typename ID, typename Functions>
	class basic_overloaded_conversion_function final : public basic_overloaded_conversion_function_helper<ID, Functions>
	{
		using MappedFunctions = basic_overloaded_conversion_function_helper<ID, Functions>::Functions;

	protected:
		constexpr return_type_reference return_type() const noexcept override final
		{
			return type::reflect<typename ID::Result>();
		}

	public:
		constexpr PP::any_view<const conversion_function&> get_conversion_overloads() const noexcept override final
		{
			return reflect_many<MappedFunctions, const conversion_function&>();
		}
	};
}
