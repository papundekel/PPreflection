#pragma once

template <typename Holdee>
class integral_promotion_type
{
	static constexpr int helper(int) noexcept { return {}; }
	static constexpr unsigned int helper(unsigned int) noexcept { return {}; }
	static constexpr long helper(long) noexcept { return {}; }
	static constexpr unsigned long helper(unsigned long) noexcept { return {}; }
	static constexpr long long helper(long long) noexcept { return {}; }
	static constexpr unsigned long long helper(unsigned long long) noexcept { return {}; }

public:
	static constexpr decltype(auto) value_f() noexcept { return helper(Holdee{}); }
};
