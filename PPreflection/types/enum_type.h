#pragma once
#include "PP/any_iterator.hpp"

#include "../named_descriptor.h"
#include "user_defined_type.h"

namespace PPreflection
{
	class enum_type;
	class dynamic_object;

	class enum_value : public detail::named_descriptor<descriptor>
	{
		constexpr virtual void print_name_before_parent(PP::simple_ostream&) const noexcept
		{}
		constexpr virtual void print_name_after_parent(PP::simple_ostream& out) const noexcept
		{
			out.write(get_name());
			//out.write(" = ");
			//out.write(get_value());
		}

		constexpr parent_descriptor_reference get_parent(void*) const noexcept override final
		{
			return {};
		}

	public:
		constexpr virtual dynamic_object get_value() const noexcept = 0;
		
		constexpr virtual const enum_type& get_parent() const noexcept = 0;
	};

	class enum_type : public user_defined_type
	{
	public:
		constexpr virtual PP::any_view<PP::iterator_category::ra, const enum_value&> get_values() const noexcept = 0;
		constexpr virtual const integral_type& get_underlying_type() const noexcept = 0;
		constexpr virtual bool is_scoped() const noexcept = 0;
		constexpr virtual bool has_fixed_underlying_type() const noexcept = 0;

		constexpr void destroy(void*) const noexcept override final
		{}

		constexpr virtual convertor_object conversion(const arithmetic_type& target) const noexcept = 0;

		constexpr standard_conversion_sequence make_standard_conversion_sequence_impl(const non_array_object_type& target) const noexcept override final;
	};
}
