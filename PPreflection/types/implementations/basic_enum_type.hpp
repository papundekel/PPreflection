#pragma once
#include "PP/concepts/enum.hpp"
#include "PP/promotion_type.hpp"
#include "PP/static_cast.hpp"
#include "PP/tuple_map.hpp"
#include "PP/tuple_to_array.hpp"

#include "../../dynamic_object.h"
#include "../../reflect.h"
#include "../enum_type.h"
#include "../make_numeric_conversion.hpp"
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
		constexpr dynamic_object get_value() const noexcept override final
		{
			return dynamic_object::create(PP_DECLTYPE(value), value);
		}
		constexpr const enum_type& get_parent() const noexcept override final
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

		static constexpr bool scoped = PP::has_implicit_conversion_to_arithmetic_type(PP::type<T>);

		static constexpr auto fixed_type = PPreflection::reflect(PP::type<tags::enum_fixed_type<T>>);
		static constexpr auto has_fixed_type = fixed_type != PP::type<void>;

		constexpr PP::any_view<PP::iterator_category::ra, const enum_value&> get_values() const noexcept override final
		{
			return enum_values_array;
		}

		constexpr convertor_object conversion(const arithmetic_type& target) const noexcept override final
		{
			return make_numeric_conversion(PP::type<T>, target);
		}

		constexpr bool is_scoped() const noexcept override final
		{
			return scoped;
		}

		constexpr bool has_fixed_underlying_type() const noexcept override final
		{
			return has_fixed_type;
		}

		constexpr const integral_type& get_underlying_type() const noexcept override final
		{
			if constexpr (!scoped)
				return type::reflect | PP::promotion_type <<= PP::type<T>;
			else
			{
				if constexpr (has_fixed_type)
					return type::reflect(PP::type<int>);
				else
					return type::reflect(fixed_type);
			}
		}
	};
}
