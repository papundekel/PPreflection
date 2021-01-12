#pragma once
#include <variant>
#include "../PP/PP/reference_wrapper.hpp"

template <typename... TypeClasses>
class type_disjunction_reference
{
	std::variant<PP::cref_t<TypeClasses>...> variant;

public:
	template <typename T>
	constexpr type_disjunction_reference(T&& t) noexcept
		: variant(std::forward<T>(t))
	{}

	template <typename T>
	constexpr bool holds_alternative() const noexcept
	{
		return std::holds_alternative<PP::cref_t<T>>(variant);
	}

	template <typename F>
	constexpr decltype(auto) visit(F&& f) const
	{
		return std::visit([&f](auto reference) -> decltype(auto) { return std::forward<F>(f)(reference.get()); }, variant);
	}
};
