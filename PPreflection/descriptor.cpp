#include "descriptor.hpp"

#include "PP/array_ostream.hpp"

#include "dynamic_object.hpp"
#include "Namespace.hpp"
#include "parent_descriptor_reference.hpp"
#include "parent_descriptor_reference_strong.hpp"
#include "types/types.hpp"
#include "functions/functions.hpp"

std::ostream& PPreflection::operator<<(std::ostream& out, const PPreflection::descriptor& d)
{
	PP::array_ostream<64> so;
	d.print_name(so);
	so.write_to_ostream(out);

	return out;
}
