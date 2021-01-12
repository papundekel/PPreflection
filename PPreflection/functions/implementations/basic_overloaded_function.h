#pragma once
#include <string_view>
#include "../../descriptor.h"
#include "any_iterator.hpp"

namespace detail
{
	template <typename ID, typename Base>
	class basic_overloaded_function : public Base::overloaded
	{
	protected:
		static constexpr auto raw_overloads = reflect(PP::type_v<reflection::overloads<ID>>);

		static constexpr auto function_overloads =
			reflect_many(raw_overloads, PP::type_v<const function&>);

	public:
		constexpr PP::any_view<const function&> get_function_overloads() const noexcept override final
		{
			return function_overloads;
		}
	};
}
