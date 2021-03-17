#include "Enum.hpp"

PPreflector::Enum::Enum(const clang::EnumType& type, const descriptor& parent)
	: node_descriptor<clang::EnumType>(type)
	, parent(parent)
{}

void PPreflector::Enum::print_metadata_name_header(llvm::raw_ostream& out) const
{
	print_name(out);
}

void PPreflector::Enum::print_metadata_name_own(llvm::raw_ostream&) const
{

}

void PPreflector::Enum::print_metadata_name_foreign(llvm::raw_ostream&) const
{

}

void PPreflector::Enum::print_metadata_implementation(llvm::raw_ostream&) const
{

}
