#pragma once
#include "string_ostream.h"
#include "simple_ostream.hpp"
#include "simple_vector.hpp"

constexpr void string_ostream::write(std::string_view s) noexcept
{
	for (char c : s)
		buffer.push_back(c);
}
