#pragma once
#include <string_view>
#include <vector>
#include <utility>
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
			std::string name;
			std::int64_t value;

		public:
			inline explicit dynamic_enum_value(std::pair<std::string_view, std::int64_t> name_value) noexcept
				: name(name_value.first)
				, value(name_value.second)
			{}

			inline std::string_view get_name() const noexcept override final
			{
				return name;
			}
			constexpr std::int64_t get_value() const noexcept override final
			{
				return value;
			}
		};

		std::vector<dynamic_enum_value> values;

	public:
		inline explicit dynamic_enum_type(
			std::string_view name,
			PP::concepts::view auto&& values,
			parent_descriptor_reference parent,
			PP::cv_qualifier cv = PP::cv_qualifier::none) noexcept
			: dynamic_user_defined_type<enum_type>(name, parent, cv)
			, values(
				PP::view_begin(PP_FORWARD(values)),
				PP::view_end(PP_FORWARD(values)))
		{}

		constexpr PP::any_view_ra<const enum_value&> get_values() const noexcept override final
		{
			return values;
		}

		constexpr virtual std::size_t size() const noexcept override final
		{
			return 8;
		}
	};
}
