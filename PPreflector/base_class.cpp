#include "base_class.hpp"

void PPreflector::base_class::print_name_header(llvm::raw_ostream&) const
{
	// print nothing
}

void PPreflector::base_class::print_name_own(llvm::raw_ostream&) const
{
	// print nothing
}

void PPreflector::base_class::print_name_foreign(llvm::raw_ostream& out) const
{
	out << "::" << PPREFLECTOR_MEMBER_PRINT(print_qualified_name, *this);
}

void PPreflector::base_class::print_metadata_object(llvm::raw_ostream&) const
{
	// print nothing
}

void PPreflector::base_class::print_metadata_members(llvm::raw_ostream&) const
{
	// print nothing
}
