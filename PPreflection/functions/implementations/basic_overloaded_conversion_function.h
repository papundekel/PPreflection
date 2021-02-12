#pragma once
#include "basic_overloaded_member_function.h"
#include "../conversion_function.h"
#include "../../types/types.h"

namespace PPreflection::detail
{
	template <typename Class, typename Return>
	class basic_overloaded_conversion_function final
		: public basic_overloaded_member_function_base<tags::conversion_function<Class, Return>, conversion_function>
	{
		constexpr return_type_reference return_type() const noexcept override final
		{
			return type::reflect(PP::type<Return>);
		}

		constexpr PP::any_view_ra<const conversion_function&> get_conversion_overloads() const noexcept override final
		{
			return this->member_function_base_overloads;
		}

		constexpr const class_type& get_parent() const noexcept override final
		{
			return type::reflect(PP::type<Class>);
		}
	};
}
