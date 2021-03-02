#pragma once
#include "../Namespace.h"
#include "function.h"

namespace PPreflection
{
	class namespace_function;

	class overloaded_namespace_function : public detail::named_descriptor<function::overloaded>
	{
	protected:
		constexpr virtual PP::any_view<PP::iterator_category::ra, const namespace_function&> get_namespace_overloads() const noexcept = 0;

	public:
		constexpr const Namespace& get_parent() const noexcept override = 0;

		constexpr PP::concepts::view auto get_overloads() const noexcept
		{
			return get_namespace_overloads();
		}
	};

	class namespace_function : public function
	{
	public:
		using overloaded = overloaded_namespace_function;

		constexpr const overloaded& get_overloaded_function() const noexcept override = 0;

		constexpr const Namespace& get_parent() const noexcept override final
		{
			return get_overloaded_function().get_parent();
		}
	};
}
