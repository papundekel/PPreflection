#pragma once
#include "simple_ostream.h"
#include "simple_vector.h"

class string_ostream final : public simple_ostream
{
	simple_vector<char> buffer;

public:
	constexpr void write(std::string_view s) noexcept override final;
	void write_to_ostream(std::ostream& out) noexcept override final;
};
