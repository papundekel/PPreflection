#pragma once
#include "ostream.hpp"

class descriptor
{
public:
	constexpr virtual void print_name(simple_ostream& out) const noexcept = 0;
};
