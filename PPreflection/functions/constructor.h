#pragma once
#include "PP/view.hpp"

#include "maybe_static_member_function.h"
#include "named_function.h"

namespace PPreflection
{
	class constructor
		: public detail::named_function<maybe_static_member_function>
	{
		inline dynamic_variable invoke_unsafe(
			PP::any_iterator<PP::iterator_category::ra, dynamic_reference>
				arg_iterator,
			void*) const override final;

	public:
		virtual dynamic_object invoke_unsafe(
			PP::any_iterator<PP::iterator_category::ra, dynamic_reference>
				arg_iterator) const = 0;

		constexpr virtual bool is_explicit() const noexcept = 0;

		constexpr bool is_converting() const noexcept
		{
			return !is_explicit() && PP::view_count(parameter_types()) == 1;
		}

		constexpr PP::string_view get_name() const noexcept override final
		{
			return get_parent().get_name();
		}
	};
}
