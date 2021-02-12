#include "../PP/PP/array_ostream.hpp"
#include "descriptor.h"

std::ostream& PPreflection::operator<<(std::ostream& out, const PPreflection::descriptor& d)
{
	PP::array_ostream<64> so;
	d.print_name(so);
	so.write_to_ostream(out);

	return out;
}
