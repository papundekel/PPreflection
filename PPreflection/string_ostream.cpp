#include "string_ostream.hpp"

void string_ostream::write_to_ostream(std::ostream& out) noexcept
{
	out.write(buffer.begin(), buffer.count());
	buffer.clear();
}
