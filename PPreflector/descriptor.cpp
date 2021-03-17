#include "descriptor.hpp"

#include "print_wrap.hpp"

PPreflector::descriptor::~descriptor()
{}

void PPreflector::descriptor::print_metadata(llvm::raw_ostream& out) const
{
	out <<	"\n"
			"// " << PPREFLECTOR_PW(print_metadata_name_header, *this) << "\n"
		<<	PPREFLECTOR_PW(print_metadata_implementation, *this);
}
