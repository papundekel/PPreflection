#include "descriptor.hpp"

#include "PP/std_ostream.hpp"

#include "parent_descriptor_reference.hpp"
#include "types/cv_type.hpp"
#include "types/non_user_defined_type.hpp"
#include "types/reference_type.hpp"

std::ostream& PPreflection::operator<<(std::ostream& out,
									   const PPreflection::descriptor& d)
{
	PP::std_ostream std_out(out);
	d.print_name(std_out);

	return out;
}
