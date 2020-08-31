#pragma once
#include "simple_ostream.h"
#include "to_chars.h"
#include <array>

constexpr void simple_ostream::write(std::size_t number) noexcept
{
	std::array<char, 32> buffer;
	auto count = to_chars(buffer.data(), buffer.data() + buffer.size(), number);
	write(std::string_view(buffer.data(), count));
}
