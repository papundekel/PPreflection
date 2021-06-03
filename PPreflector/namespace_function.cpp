#include "namespace_function.hpp"

void PPreflector::namespace_function::print_metadata_object(
	llvm::raw_ostream& out) const
{
	out << printer_metadata(PPREFLECTOR_MEMBER_PRINT(print_name_own, *this))
		<< "PPreflection::detail::basic_namespace_function<"
		<< PPREFLECTOR_MEMBER_PRINT(print_name_foreign, *this) << ">{};\n";
}
