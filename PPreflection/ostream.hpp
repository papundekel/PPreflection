#pragma once
#include <ostream>
#include "simple_vector.hpp"

class simple_ostream
{
public:
	constexpr virtual void write(const char* s) noexcept = 0;

	void virtual write_to_ostream(std::ostream& out) noexcept = 0;
};

template <std::size_t count>
class array_ostream : public simple_ostream
{
	std::array<char, count> buffer;
	std::size_t position;

	constexpr auto advance_head() noexcept
	{
		auto copy = position++;

		if (position == buffer.size())
			position = 0;

		return copy;
	}

public:
	constexpr void write(const char* s) noexcept override
	{
		for (auto i = s; *i != 0; ++i)
			buffer[advance_head()] = *i;
	}

	void write_to_ostream(std::ostream& out) noexcept override
	{
		out.write(buffer.begin(), buffer.begin() + position);
		position = 0;
	}
};

class string_ostream : public simple_ostream
{
	simple_vector<char> buffer;

public:
	constexpr void write(const char* s) noexcept override
	{
		for (auto i = s; *i != 0; ++i)
			buffer.push_back(*i);
	}

	void write_to_ostream(std::ostream& out) noexcept override
	{
		out.write(buffer.begin(), buffer.count());
		buffer.clear();
	}
};
