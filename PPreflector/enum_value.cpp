#include "enum_value.hpp"

#include "printers.hpp"

PPreflector::enum_value::enum_value(const clang::EnumConstantDecl& decl)
	: node_descriptor<clang::EnumConstantDecl, descriptor>(decl)
{}

void PPreflector::enum_value::print_name_header(llvm::raw_ostream&) const
{
	// print nothing
}

void PPreflector::enum_value::print_name_own(llvm::raw_ostream& out) const
{
	out << "PP::value_t<" << PPREFLECTOR_MEMBER_PRINT(print_name_foreign, *this) << ">";
}

void PPreflector::enum_value::print_name_foreign(llvm::raw_ostream& out) const
{
	out << "::" << PPREFLECTOR_MEMBER_PRINT(print_qualified_name, *this);
}

void PPreflector::enum_value::print_metadata_object(llvm::raw_ostream&) const
{
	// print nothing
}

void PPreflector::enum_value::print_metadata_members(llvm::raw_ostream&) const
{
	// print nothing
}

const PPreflector::descriptor* PPreflector::enum_value::get_parent(void*) const
{
	return nullptr;
}
