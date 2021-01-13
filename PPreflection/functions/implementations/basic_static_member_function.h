#pragma once
#include "../static_member_function.h"
#include "basic_static_function.h"

namespace detail
{
	template <auto f>
	class basic_static_member_function : public basic_static_function<f, static_member_function>
	{
		constexpr const static_member_function::overloaded& get_overloaded_function() const noexcept override final
		{
			return reflect(reflect(PP::type_v<reflection::overloads<PP::value_t<f>>>));
		}
	};
}
