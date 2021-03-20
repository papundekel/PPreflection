#include "global_namespace.hpp"

#include "Enum.hpp"
#include "Class.hpp"
#include "non_global_namespace.hpp"

void PPreflector::global_namespace::print_name_parent(llvm::raw_ostream& out) const
{
	out << "PPreflection::tags";
}
void PPreflector::global_namespace::print_qualified_name(llvm::raw_ostream&) const
{
	// print nothing
}
void PPreflector::global_namespace::print_name(llvm::raw_ostream& out) const
{
	out << "global";
}
void PPreflector::global_namespace::print_preamble(llvm::raw_ostream&) const
{
	// print nothing
}

void PPreflector::global_namespace::print_unscoped_name(llvm::raw_ostream&) const
{
	// print nothing
}
void PPreflector::global_namespace::print_scoped_name_parent(llvm::raw_ostream&) const
{
	// print nothing
}
void PPreflector::global_namespace::print_scoped_name_as_parent(llvm::raw_ostream&) const
{
	// print nothing
}

PPreflector::global_namespace::global_namespace()
	: Namespace(0)
{}

const PPreflector::descriptor* PPreflector::global_namespace::get_parent(void*) const
{
	return nullptr;
}
