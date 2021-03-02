#pragma once
#include "PP/string_view.hpp"
#include "PP/simple_vector.hpp"

#include "enum_type.h"
#include "dynamic_cv_qualifiable_type.h"
#include "dynamic_user_defined_type.h"
#include "dynamic_named_descriptor.h"

namespace PPreflection
{
	class dynamic_enum_type final : public detail::dynamic_user_defined_type<enum_type>
	{
		class dynamic_enum_value final : public enum_value
		{
			PP::simple_vector<char> name;
			long long value;

		public:
			constexpr dynamic_enum_value(PP::string_view name, long long value) noexcept
				: name()
				, value(value)
			{
				for (char c : name)
					this->name.push_back(c);
			}

			constexpr PP::string_view get_name() const noexcept override final
			{
				return name;
			}
			constexpr long long get_value() const noexcept override final
			{
				return value;
			}
		};

		PP::simple_vector<dynamic_enum_value> values;
		const non_void_fundamental_type& underlying_type;

	public:
		constexpr dynamic_enum_type(
			PP::string_view name,
			PP::concepts::view auto&& values,
			const non_void_fundamental_type& underlying_type,
			parent_descriptor_reference parent,
			PP::cv_qualifier cv = PP::cv_qualifier::none) noexcept

			: dynamic_user_defined_type<enum_type>(name, parent, cv)
			, values(PP_FORWARD(values))
			, underlying_type(underlying_type)
		{}

		constexpr PP::any_view<PP::iterator_category::ra, const enum_value&> get_values() const noexcept override final
		{
			return values;
		}

		constexpr const non_void_fundamental_type& get_underlying_type() const noexcept override final
		{
			return underlying_type;
		}

		constexpr virtual size_t size() const noexcept override final
		{
			return 8;
		}
	};
}
