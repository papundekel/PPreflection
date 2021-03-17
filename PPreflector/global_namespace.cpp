#include "global_namespace.hpp"

#include "Enum.hpp"
#include "Class.hpp"
#include "non_global_namespace.hpp"

void PPreflector::global_namespace::print_name_parent(llvm::raw_ostream& out) const
{
	out << "PPreflection::tags";
}
void PPreflector::global_namespace::print_name_simple(llvm::raw_ostream& out) const
{
	out << "::";
}
void PPreflector::global_namespace::print_name_simple_no_prefix(llvm::raw_ostream&) const
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

PPreflector::global_namespace::global_namespace()
	: Namespace(0)
{}
