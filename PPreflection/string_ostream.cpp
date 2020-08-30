#include "simple_ostream.hpp"
#include "string_ostream.hpp"
#include "to_chars.hpp"

void string_ostream::write_to_ostream(std::ostream& out) noexcept
{
	out.write(buffer.begin(), buffer.count());
	buffer.clear();
}
