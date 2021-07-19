#include "non_conversion_member_function.hpp"

void PPreflector::non_conversion_member_function::print_metadata_traits(
	llvm::raw_ostream& out) const
{
	out << PPREFLECTOR_MEMBER_PRINT(print_metadata_name, *this) << "\n"
		<< PPREFLECTOR_MEMBER_PRINT(print_metadata_parent, *this) << "\n";
}

void PPreflector::non_conversion_member_function::print_metadata_object(
	llvm::raw_ostream& out) const
{
	out << printer_metadata_descriptor(
			   PPREFLECTOR_MEMBER_PRINT(print_name_own, *this))
		<< "basic_non_conversion_member_function<"
		<< PPREFLECTOR_MEMBER_PRINT(print_name_foreign, *this) << ">{};\n";
}
