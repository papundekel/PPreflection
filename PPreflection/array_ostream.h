#pragma once
#include "simple_ostream.h"

template <std::size_t count>
class array_ostream final : public simple_ostream
{
	std::array<char, count> buffer;
	std::size_t position;

public:
	constexpr array_ostream() noexcept;

	constexpr void write(std::string_view s) noexcept override final;

	void write_to_ostream(std::ostream& out) noexcept override final;
};
