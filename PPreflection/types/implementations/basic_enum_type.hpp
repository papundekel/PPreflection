#pragma once
#include "basic_user_defined_type.hpp"
#include "../enum_type.h"
#include "../../reflect.h"
#include "tuple_map.hpp"
#include "tuple_map_to_array.hpp"
#include "functional/id.hpp"

namespace detail
{
	template <auto value>
	class basic_enum_value final : public enum_value
	{
		constexpr std::string_view get_name() const noexcept override final
		{
			return ::reflect(PP::type_v<reflection::name<PP::value_t<value>>>);
		}
		constexpr std::int64_t get_value() const noexcept override final
		{
			return std::int64_t(value);
		}
	public:
		constexpr basic_enum_value(PP::type_t<PP::value_t<value>>) noexcept
		{}
	};

	template <typename T>
	class basic_enum_type final : public basic_user_defined_type<T, enum_type>
	{
		static_assert(std::is_enum_v<T>);

		static constexpr auto enum_values_basic =
			PP::tuple_map([](auto v) { return basic_enum_value(v); }, ::reflect(PP::type_v<reflection::enum_values<T>>));

		static constexpr auto enum_values_array = PP::tuple_map_to_array(PP::id<const enum_value&>, enum_values_basic);

		constexpr PP::any_view<const enum_value&> get_values() const noexcept override final
		{
			return enum_values_array;
		}
	};
}
