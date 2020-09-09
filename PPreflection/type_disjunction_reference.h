#pragma once
#include <variant>
#include "cref_t.hpp"

template <typename... TypeClasses>
class type_disjunction_reference
{
	std::variant<cref_t<TypeClasses>...> variant;

public:
	template <typename T>
	constexpr type_disjunction_reference(T&& t) noexcept
		: variant(std::forward<T>(t))
	{}

	template <typename T>
	constexpr bool holds_alternative() const noexcept
	{
		return std::holds_alternative<cref_t<T>>(variant);
	}

	template <typename F>
	constexpr decltype(auto) visit(F&& f) const noexcept(std::visit(std::forward<F>(f), variant))
	{
		return std::visit(std::forward<F>(f), variant);
	}
};
