#include "descriptor.h"

#include "PP/array_ostream.hpp"

std::ostream& PPreflection::operator<<(std::ostream& out, const PPreflection::descriptor& d)
{
	PP::array_ostream<64> so;
	d.print_name(so);
	so.write_to_ostream(out);

	return out;
}
