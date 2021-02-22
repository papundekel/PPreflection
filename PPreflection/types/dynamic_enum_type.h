#pragma once
#include "enum_type.h"
#include "dynamic_cv_qualifiable_type.h"
#include "dynamic_user_defined_type.h"
#include "dynamic_named_descriptor.h"
#include "string_view.hpp"
#include "simple_vector.hpp"

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

	public:
		constexpr dynamic_enum_type(
			PP::string_view name,
			PP::concepts::view auto&& values,
			parent_descriptor_reference parent,
			PP::cv_qualifier cv = PP::cv_qualifier::none) noexcept

			: dynamic_user_defined_type<enum_type>(name, parent, cv)
			, values(
				PP::view_begin(PP_FORWARD(values)),
				PP::view_end(PP_FORWARD(values)))
		{}

		constexpr PP::any_view<PP::iterator_category::ra, const enum_value&> get_values() const noexcept override final
		{
			return values;
		}

		constexpr virtual size_t size() const noexcept override final
		{
			return 8;
		}
	};
}
