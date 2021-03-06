#pragma once
#include <variant>

#include "PP/forward_wrap.hpp"

namespace PPreflection
{
	template <typename T>
	struct type_disjunction_reference_wrap
	{
		const T& ref;

		constexpr type_disjunction_reference_wrap(const T& ref) noexcept
			: ref(ref)
		{}
	};
	template <typename... TypeClasses>
	class type_disjunction_reference
	{
		std::variant<type_disjunction_reference_wrap<TypeClasses>...> v;

	public:
		constexpr type_disjunction_reference(const auto& t) noexcept
			: v(type_disjunction_reference_wrap(t))
		{}
		type_disjunction_reference(const type_disjunction_reference&) = default;

		constexpr bool holds_alternative(PP::concepts::type auto t) const noexcept
		{
			return std::holds_alternative<PP_GET_TYPE(PP::Template<type_disjunction_reference_wrap>(t))>(v);
		}

		constexpr decltype(auto) visit(auto&& f) const
		{
			return std::visit([f_wrap = PP_FORWARD_WRAP(f)]
				<typename T>
				(type_disjunction_reference_wrap<T> wrap) -> decltype(auto)
				{
					return f_wrap.unwrap()(wrap.ref);
				}, v);
		}
	};
}
