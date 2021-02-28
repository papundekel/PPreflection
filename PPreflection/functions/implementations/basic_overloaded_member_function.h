#pragma once
#include "../member_function.h"
#include "basic_overloaded_function.h"

namespace PPreflection::detail
{
	template <typename ID, typename Base>
	class basic_overloaded_member_function : public basic_overloaded_function<ID, Base>
	{
	protected:
		static constexpr auto member_function_base_overloads = reflect_many(
			PP::type<const Base&>,
			basic_overloaded_member_function::raw_overloads);

	private:
		constexpr PP::any_view<PP::iterator_category::ra, const member_function&> get_member_function_overloads() const noexcept override final
		{
			return member_function_base_overloads;
		}
	};
}
