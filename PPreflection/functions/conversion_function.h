#pragma once
#include "PP/view_prefix.hpp"

#include "member_function.h"

namespace PPreflection
{
	class conversion_function : public member_function
	{
		friend class conversion_function_olr;
		
	protected:
		constexpr virtual dynamic_variable invoke_unsafe(dynamic_reference caller) const = 0;

		dynamic_variable invoke_unsafe(dynamic_reference caller, PP::any_iterator<PP::iterator_category::ra, dynamic_reference>) const override final
		{
			return invoke_unsafe(caller);
		}
	public:
		constexpr virtual bool is_explicit() const noexcept = 0;

		constexpr bool has_name(PP::string_view) const noexcept override final
		{
			return false;
		}

		constexpr void print_name_implementation(PP::simple_ostream& out) const noexcept override final
		{
			out.write("operator ");
			const type& rt = return_type();
			rt.print_name(out);
		}

		dynamic_variable invoke(dynamic_reference) const
		{
			return dynamic_variable::create_invalid(dynamic_object::invalid_code::implicit_conversion_error);
		}
	};
}
