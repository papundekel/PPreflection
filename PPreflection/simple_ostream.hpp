#pragma once
#include <array>
#include "simple_ostream.h"
#include "to_chars.h"

constexpr void simple_ostream::write(std::size_t x) noexcept
{
	std::array<char, 32> buffer = {};
	auto length = to_chars(buffer.data(), buffer.data() + buffer.size(), x);
	write({ buffer.data(), length });
}
