#pragma once
#include "PP/view.hpp"

#include "maybe_static_member_function.h"

namespace PPreflection
{
	class constructor : public detail::maybe_static_member_function
	{
		virtual dynamic_object invoke_unsafe(PP::any_iterator<PP::iterator_category::ra, dynamic_reference> arg_iterator) const noexcept = 0;
		inline dynamic_variable invoke_unsafe(PP::any_iterator<PP::iterator_category::ra, dynamic_reference> arg_iterator, void*) const noexcept override final;

	public:
		inline dynamic_object invoke(PP::any_view<PP::iterator_category::ra, dynamic_reference> args = {}) const noexcept;

		constexpr virtual bool is_explicit() const noexcept = 0;

		constexpr bool is_converting() const noexcept
		{
			return !is_explicit() && PP::view_count(parameter_types()) == 1;
		}
	};
}
