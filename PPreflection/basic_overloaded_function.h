#pragma once
#include <string_view>
#include "simple_ostream.h"

template <typename ID, typename Base>
class basic_overloaded_function : public Base
{
public:
	constexpr void print_name(simple_ostream& out) const noexcept override final;
	constexpr bool has_name(std::string_view name) const noexcept override final;
};
