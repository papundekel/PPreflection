#include "default_constructor.hpp"

PPreflector::default_constructor::default_constructor(const descriptor& parent)
	: constructor(parent)
{}

void PPreflector::default_constructor::print_name_header(
	llvm::raw_ostream& out) const
{
	out << PPREFLECTOR_MEMBER_PRINT(print_qualified_name, get_parent())
		<< "::" << PPREFLECTOR_MEMBER_PRINT(print_name, get_parent()) << "()";
}
void PPreflector::default_constructor::print_name_own(llvm::raw_ostream&) const
{}
void PPreflector::default_constructor::print_name_foreign(
	llvm::raw_ostream&) const
{}

void PPreflector::default_constructor::print_metadata_members(
	llvm::raw_ostream&) const
{}
void PPreflector::default_constructor::print_metadata_traits(
	llvm::raw_ostream&) const
{}
void PPreflector::default_constructor::print_metadata_object(
	llvm::raw_ostream&) const
{}

void PPreflector::default_constructor::print_qualified_name(
	llvm::raw_ostream&) const
{}
void PPreflector::default_constructor::print_name(llvm::raw_ostream&) const
{}
