#include "conversion_function.hpp"

void PPreflector::conversion_function::print_metadata_object(llvm::raw_ostream& out) const
{
	out << printer_metadata(PPREFLECTOR_MEMBER_PRINT(print_name_own, *this)) << "PPreflection::detail::basic_conversion_function<" << PPREFLECTOR_MEMBER_PRINT(print_name_foreign, *this) << ">{};\n";
}

void PPreflector::conversion_function::print_metadata_members(llvm::raw_ostream& out) const
{
	out << PPREFLECTOR_MEMBER_PRINT(print_metadata_parent, *this) << "\n";
	
	if (this->get_node().isExplicit())
		out << printer_metadata(metadata_tag_printer<"is_explicit"_str>(PPREFLECTOR_MEMBER_PRINT(print_name_own, *this))) << "PP::value_true;\n";
}
