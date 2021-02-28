#pragma once
#include "../../descriptor.h"
#include "any_iterator.hpp"

namespace PPreflection::detail
{
	template <typename ID, typename Base>
	class basic_overloaded_function : public Base::overloaded
	{
	protected:
		static constexpr auto raw_overloads = reflect(PP::type<PPreflection::tags::overloads<ID>>);
		static constexpr auto function_overloads = reflect_many(PP::type<const function&>, raw_overloads);

	private:
		constexpr PP::any_view<PP::iterator_category::ra, const function&> get_function_overloads() const noexcept override final
		{
			return function_overloads;
		}
	};
}
