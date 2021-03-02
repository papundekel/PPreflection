#pragma once
#include "PP/any_iterator.hpp"

#include "../named_descriptor.h"
#include "user_defined_type.h"

namespace PPreflection
{
	class enum_value : public detail::named_descriptor<descriptor>
	{
		constexpr virtual void print_name_before_parent(PP::simple_ostream&) const noexcept
		{}
		constexpr virtual void print_name_after_parent(PP::simple_ostream& out) const noexcept
		{
			out.write(get_name());
			out.write(" = ");
			out.write(get_value());
		}

	public:
		constexpr virtual long long get_value() const noexcept = 0;
	};

	class enum_type : public user_defined_type
	{
	public:
		constexpr virtual PP::any_view<PP::iterator_category::ra, const enum_value&> get_values() const noexcept = 0;
		constexpr virtual const non_void_fundamental_type& get_underlying_type() const noexcept = 0;
		
		constexpr void destroy(void*) const noexcept override final
		{}
	};
}
