#include "base_class.hpp"

PPreflector::base_class::base_class(const clang::Type& t)
	: node_descriptor<clang::Type, descriptor>(t)
{}

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
