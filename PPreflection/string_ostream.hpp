#pragma once
#include "string_ostream.h"
#include "simple_ostream.h"
#include "simple_vector.h"

constexpr void string_ostream::write(std::string_view s) noexcept
{
	for (char c : s)
		buffer.push_back(c);
}
