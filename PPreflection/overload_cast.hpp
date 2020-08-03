#pragma once

template <typename... Args>
struct overload_caster
{
	template <typename Return>
	static constexpr decltype(auto) cast(Return(&f)(Args...))
	{
		return f;
	}
};
