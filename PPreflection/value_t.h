#pragma once

template <auto V>
struct value_t
{
	static constexpr const auto& value_f() noexcept
	{
		return V;
	}
};
