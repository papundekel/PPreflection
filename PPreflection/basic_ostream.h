#pragma once
#include "simple_ostream.h"

template <template <typename> typename Buffer>
class basic_ostream final : public simple_ostream
{
	Buffer<char> buffer;

public:
	constexpr void write(std::string_view s) noexcept override final;
	void write_to_ostream(std::ostream& out) noexcept override final;
};
