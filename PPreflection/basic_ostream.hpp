#pragma once
#include "basic_ostream.h"
#include "simple_ostream.hpp"

template <template <typename> typename Buffer>
constexpr void basic_ostream<Buffer>::write(std::string_view s) noexcept
{
	for (char c : s)
		buffer.push_back(c);
}

template <template <typename> typename Buffer>
void basic_ostream<Buffer>::write_to_ostream(std::ostream& out) noexcept
{
	out.write(buffer.begin(), buffer.count());
	buffer.clear();
}
