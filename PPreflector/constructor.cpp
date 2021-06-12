#include "constructor.hpp"

void PPreflector::constructor::print_name_header(llvm::raw_ostream& out) const
{
	out << PPREFLECTOR_MEMBER_PRINT(print_qualified_name, get_parent())
		<< "::" << PPREFLECTOR_MEMBER_PRINT(print_name, get_parent()) << "("
		<< PPREFLECTOR_MEMBER_PRINT(print_parameter_types, *this) << ")";
}

void PPreflector::constructor::print_name_own(llvm::raw_ostream& out) const
{
	out << printer_type_tuple(
		PPREFLECTOR_MEMBER_PRINT(print_parameter_types, *this));
}

void PPreflector::constructor::print_name_foreign(llvm::raw_ostream& out) const
{
	out << printer_type_tuple(
		PPREFLECTOR_MEMBER_PRINT(print_parameter_types, *this));
}

void PPreflector::constructor::print_metadata_object(
	llvm::raw_ostream& out) const
{
	out << printer_metadata(metadata_tag_printer<"constructor"_str>(
			   PPREFLECTOR_MEMBER_PRINT(print_id, *this)))
		<< "basic_constructor<" << PPREFLECTOR_MEMBER_PRINT(print_id, *this)
		<< ">{};";
}

void PPreflector::constructor::print_metadata_traits(
	llvm::raw_ostream& out) const
{
	if (this->get_node().isExplicit())
		out << printer_metadata(metadata_tag_printer<"is_explicit"_str>(
				   PPREFLECTOR_MEMBER_PRINT(print_id, *this)))
			<< "PP::value_true;\n";
}

void PPreflector::constructor::print_id(llvm::raw_ostream& out) const
{
	out << PPREFLECTOR_MEMBER_PRINT(print_name_foreign, get_parent())
		<< PPREFLECTOR_MEMBER_PRINT(print_parameter_types_leading_comma, *this);
}
