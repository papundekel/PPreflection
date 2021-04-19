#include "descriptor.hpp"

#include "PP/array_ostream.hpp"

#include "parent_descriptor_reference.hpp"
#include "types/cv_type.hpp"
#include "types/non_user_defined_type.hpp"
#include "types/reference_type.hpp"

std::ostream& PPreflection::operator<<(std::ostream& out, const PPreflection::descriptor& d)
{
	PP::array_ostream<64> so;
	d.print_name(so);
	so.write_to_ostream(out);

	return out;
}
