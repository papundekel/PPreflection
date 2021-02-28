#pragma once
#include "basic_overloaded_function.h"
#include "basic_overloaded_named_function.h"
#include "../static_member_function.h"

namespace PPreflection::detail
{
	template <typename ID>
	class basic_overloaded_static_member_function final : public
		basic_overloaded_named_function<ID, basic_overloaded_function<ID, static_member_function>>
	{
		static constexpr auto static_member_overloads = reflect_many(
			PP::type<const static_member_function&>,
			basic_overloaded_static_member_function::raw_overloads);

		constexpr PP::any_view<PP::iterator_category::ra, const static_member_function&> get_static_member_overloads() const noexcept override final
		{
			return static_member_overloads;
		}

		constexpr const class_type& get_parent() const noexcept override final
		{
			return reflect(reflect(PP::type<tags::parent<ID>>));
		}
	};
}
