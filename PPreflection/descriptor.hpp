#pragma once
#include "simple_ostream.hpp"

class descriptor
{
public:
	constexpr virtual void print_name(simple_ostream& out) const noexcept = 0;
	constexpr virtual bool has_name(std::string_view name) const noexcept = 0;
};

std::ostream& operator<<(std::ostream& out, const descriptor& d);
