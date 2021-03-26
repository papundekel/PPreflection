#pragma once
#include "../types/function_type.h"
#include "maybe_static_member_function.h"

namespace PPreflection
{
	class class_type;
	class reference_type;

	class member_function : public detail::maybe_static_member_function
	{
		virtual dynamic_variable invoke_unsafe(dynamic_reference caller, PP::any_iterator<PP::iterator_category::ra, dynamic_reference> arg_iterator) const = 0;

	protected:
		inline dynamic_variable invoke_unsafe(PP::any_iterator<PP::iterator_category::ra, dynamic_reference> arg_iterator, void*) const noexcept override final;

	public:
		constexpr void print_name_after_parent(PP::simple_ostream& out) const noexcept override final;

		constexpr PP::ref_qualifier get_ref_qualifier() const noexcept
		{
			return get_function_type().get_function_ref_qualifier();
		}
		constexpr PP::cv_qualifier get_cv_qualifier() const noexcept
		{
			return get_function_type().get_function_cv_qualifier();
		}

		inline dynamic_variable invoke(dynamic_reference caller, PP::any_view<PP::iterator_category::ra, dynamic_reference> args = {}) const;
	};
}
