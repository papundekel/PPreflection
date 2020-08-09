#pragma once
#include <ostream>
#include <string_view>

class simple_ostream
{
public:
	constexpr virtual void write(std::string_view) noexcept = 0;
	void virtual write_to_ostream(std::ostream& out) noexcept = 0;

	constexpr void write(std::size_t x) noexcept;
};
