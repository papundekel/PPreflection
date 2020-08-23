#include "unique_raw_pointer.hpp"
#include "unique_pointer.hpp"
#include "dynamic_block.hpp"
#include "simple_vector.hpp"
#include "simple_ostream.hpp"
#include "string_ostream.hpp"
#include "to_chars.hpp"

void string_ostream::write_to_ostream(std::ostream& out) noexcept
{
	out.write(buffer.begin(), buffer.count());
	buffer.clear();
}
