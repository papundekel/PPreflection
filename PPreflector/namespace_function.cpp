#include "namespace_function.hpp"

void PPreflector::namespace_function::print_metadata_object(
	llvm::raw_ostream& out) const
{
	out << printer_metadata_descriptor(
			   PPREFLECTOR_MEMBER_PRINT(print_name_own, *this))
		<< "basic_namespace_function<"
		<< PPREFLECTOR_MEMBER_PRINT(print_name_foreign, *this) << ">{};\n";
}
