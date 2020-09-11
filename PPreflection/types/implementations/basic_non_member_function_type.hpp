#pragma once
#include <type_traits>
#include "basic_referencable_type.hpp"
#include "../non_member_function_type.h"
#include "get_function_info.hpp"
#include "../../reflect.h"

namespace detail
{
	template <typename T, typename Base>
	class basic_non_member_function_type_base : public basic_referencable_type<T, Base>
	{
		static_assert(std::is_function_v<T>);

		constexpr return_type_reference return_type() const noexcept override final
		{
			return type::reflect<typename PP::get_function_info<T>::return_type>();
		}
		constexpr PP::any_view<parameter_type_reference> parameter_types() const noexcept override final
		{
			return reflect_many<typename PP::get_function_info<T>::parameter_types, parameter_type_reference>();
		}
		constexpr bool is_noexcept() const noexcept override final
		{
			return PP::get_function_info<T>::Noexcept;
		}
	};

	template <typename T>
	using basic_non_member_function_type = basic_non_member_function_type_base<T, non_member_function_type>;
}
