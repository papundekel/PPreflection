#include "descriptor.hpp"
#include "array_ostream.hpp"

std::ostream& operator<<(std::ostream& out, const descriptor& d)
{
	array_ostream<100> so;
	d.print_name(so);
	so.write_to_ostream(out);

	return out;
}
