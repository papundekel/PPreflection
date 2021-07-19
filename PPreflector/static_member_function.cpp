#include "static_member_function.hpp"

void PPreflector::static_member_function::print_metadata_object(
	llvm::raw_ostream& out) const
{
	out << printer_metadata_descriptor(
			   PPREFLECTOR_MEMBER_PRINT(print_name_own, *this))
		<< "basic_static_member_function<"
		<< PPREFLECTOR_MEMBER_PRINT(print_name_foreign, *this) << ">{};";
}
