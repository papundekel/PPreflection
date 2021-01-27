#pragma once
#include "type_t.hpp"

template <typename Holdee>
class integral_promotion_type
{
	static constexpr int helper(int);
	static constexpr unsigned int helper(unsigned int);
	static constexpr long helper(long);
	static constexpr unsigned long helper(unsigned long);
	static constexpr long long helper(long long);
	static constexpr unsigned long long helper(unsigned long long);

public:
	static constexpr auto value_f() noexcept { return PP::type<decltype(helper(Holdee{}))>; }
};
