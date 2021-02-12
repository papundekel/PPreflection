#pragma once
#include "../namespace_function.h"
#include "basic_static_function.h"

namespace PPreflection::detail
{
	template <auto f>
	class basic_namespace_function : public basic_static_function<f, namespace_function>
	{
		constexpr const namespace_function::overloaded& get_overloaded_function() const noexcept override final
		{
			return reflect(reflect(PP::type<tags::overloads<PP::value_t<f>>>));
		}
	};
}
