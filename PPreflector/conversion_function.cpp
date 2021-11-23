#include "conversion_function.hpp"

void PPreflector::conversion_function::print_metadata_object(
	llvm::raw_ostream& out) const
{
	out << printer_metadata_descriptor(
			   PPREFLECTOR_MEMBER_PRINT(print_name_own, *this))
		<< "basic_conversion_function<"
		<< PPREFLECTOR_MEMBER_PRINT(print_name_foreign, *this) << ">{};";
}

void PPreflector::conversion_function::print_metadata_traits(
	llvm::raw_ostream& out) const
{
	out << PPREFLECTOR_MEMBER_PRINT(print_metadata_parent, *this);

	if (this->get_node().isExplicit())
	{
		out << "\n"
			<< printer_metadata(metadata_tag_printer<"is_explicit"_str>(
				   PPREFLECTOR_MEMBER_PRINT(print_name_own, *this)))
			<< "PP::value_true;";
	}
}
