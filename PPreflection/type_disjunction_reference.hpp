#pragma once
#include <variant>
#include "reference_wrapper.hpp"

namespace PPreflection
{
	template <typename... TypeClasses>
	class type_disjunction_reference
	{
		std::variant<PP::clref_t<TypeClasses>...> v;

	public:
		template <typename T>
		constexpr type_disjunction_reference(T&& t) noexcept
			: v(PP_FORWARD(t))
		{}

		template <typename T>
		constexpr bool holds_alternative() const noexcept
		{
			return std::holds_alternative<PP::clref_t<T>>(v);
		}

		template <typename F>
		constexpr decltype(auto) visit(F&& f) const
		{
			return std::visit(PP::cal * PP::ref(f) | PP::unref, v);
		}
	};
}
