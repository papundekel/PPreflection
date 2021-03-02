#pragma once
#include "../namespace_function.h"
#include "basic_overloaded_function.h"
#include "basic_overloaded_named_function.h"

namespace PPreflection::detail
{
	template <typename ID>
	class basic_overloaded_namespace_function final : public
		basic_overloaded_named_function<ID, basic_overloaded_function<ID, namespace_function>>
	{
		static constexpr auto namespace_overloads = reflect_many(
			PP::type<const namespace_function&>,
			basic_overloaded_namespace_function::raw_overloads);

		constexpr PP::any_view<PP::iterator_category::ra, const namespace_function&> get_namespace_overloads() const noexcept override final
		{
			return namespace_overloads;
		}

		constexpr const Namespace& get_parent() const noexcept override final
		{
			return reflect(reflect(PP::type<tags::parent<ID>>));
		}
	};
}
