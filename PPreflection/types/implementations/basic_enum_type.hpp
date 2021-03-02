#pragma once
#include "PP/concepts/enum.hpp"
#include "PP/static_cast.hpp"
#include "PP/tuple_map.hpp"
#include "PP/tuple_to_array.hpp"

#include "../../reflect.h"
#include "../enum_type.h"
#include "basic_user_defined_type.hpp"

namespace PPreflection::detail
{
	template <auto value>
	class basic_enum_value final : public enum_value
	{
		constexpr PP::string_view get_name() const noexcept override final
		{
			return PPreflection::reflect(PP::type<tags::name<PP::value_t<value>>>);
		}
		constexpr long long get_value() const noexcept override final
		{
			return (long long)value;
		}
		constexpr const descriptor& get_parent() const noexcept override final
		{
			return type::reflect(PP_DECLTYPE(value));
		}
	};

	PP_FUNCTOR(make_basic_enum_value, PP::concepts::value auto v)
	{
		return basic_enum_value<PP_GET_VALUE(v)>{};
	});

	template <typename T>
	class basic_enum_type final : public basic_user_defined_type<T, enum_type>
	{
		static_assert(PP::concepts::enum_type<T>);

		static constexpr auto enum_values_basic = make_basic_enum_value + PPreflection::reflect(PP::type<tags::enum_values<T>>);

		static constexpr auto enum_values_array = PP::static__cast * PP::type<const enum_value&> << enum_values_basic;

		constexpr PP::any_view<PP::iterator_category::ra, const enum_value&> get_values() const noexcept override final
		{
			return enum_values_array;
		}

		constexpr const non_void_fundamental_type& get_underlying_type() const noexcept override final
		{
			return type::reflect(PP::type<int>);
		}
	};
}
