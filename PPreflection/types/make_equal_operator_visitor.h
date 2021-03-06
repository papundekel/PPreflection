#pragma once

namespace PPreflection
{
	constexpr auto make_equal_operator_visitor(auto reference) noexcept
	{
		return [reference]
			(const auto& t)
			{
				return reference.visit(PP::overloaded
				(
					[&t]
					(decltype(t) u)
					{
						return t == u;
					},
					[](auto&) { return false; }
				));
			};
	}
}
