#pragma once
#include "PP/string_view.hpp"
#include "PP/simple_vector.hpp"

#include "../dynamic_object.h"
#include "dynamic_user_defined_type.h"
#include "dynamic_named_descriptor.h"
#include "enum_type.h"

namespace PPreflection
{
	class dynamic_enum_type final : public detail::dynamic_user_defined_type<enum_type>
	{
		class dynamic_enum_value final : public enum_value
		{
			PP::simple_vector<char> name;
			dynamic_object value;
			const enum_type& parent;

		public:
			constexpr dynamic_enum_value(PP::string_view name, dynamic_object&& value, const enum_type& parent) noexcept
				: name()
				, value(PP::move(value))
				, parent(parent)
			{
				for (char c : name)
					this->name.push_back(c);
			}

			constexpr PP::string_view get_name() const noexcept override final
			{
				return name;
			}
			constexpr dynamic_object get_value() const noexcept override final
			{
				return dynamic_object::create_shallow_copy(value);
			}

			constexpr const enum_type& get_parent() const noexcept override final
			{
				return parent;
			}
		};

		PP::simple_vector<dynamic_enum_value> values;
		const integral_type& underlying_type;

	public:
		constexpr dynamic_enum_type(
			PP::string_view name,
			PP::concepts::view auto&& values,
			const integral_type& underlying_type,
			parent_descriptor_reference_strong parent) noexcept

			: dynamic_user_defined_type<enum_type>(name, parent)
			, values(PP_FORWARD(values))
			, underlying_type(underlying_type)
		{}

		constexpr PP::any_view<PP::iterator_category::ra, const enum_value&> get_values() const noexcept override final
		{
			return values;
		}

		constexpr const integral_type& get_underlying_type() const noexcept override final
		{
			return underlying_type;
		}

		constexpr virtual PP::size_t size() const noexcept override final
		{
			return 8;
		}
	};
}
