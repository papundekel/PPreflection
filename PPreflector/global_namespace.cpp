#include "global_namespace.hpp"

#include "Class.hpp"
#include "Enum.hpp"
#include "non_global_namespace.hpp"

PPreflector::global_namespace::global_namespace()
	: Namespace(0)
{}

void
PPreflector::global_namespace::print_name_parent(llvm::raw_ostream& out) const
{
	out << "PPreflection::tags";
}

void
PPreflector::global_namespace::print_qualified_name(llvm::raw_ostream&) const
{
	// print nothing
}

void
PPreflector::global_namespace::print_name(llvm::raw_ostream& out) const
{
	out << "global";
}

void
PPreflector::global_namespace::print_unscoped_name(llvm::raw_ostream&) const
{
	// print nothing
}

void
PPreflector::global_namespace::print_scoped_name_parent(
	llvm::raw_ostream&) const
{
	// print nothing
}

void
PPreflector::global_namespace::print_scoped_name_as_parent(
	llvm::raw_ostream&) const
{
	// print nothing
}

void
PPreflector::global_namespace::print_metadata_object(
	llvm::raw_ostream& out) const
{
	out << "template <> constexpr inline auto "
		   "PPreflection::detail::metadata<PPreflection::tags::global> = "
		   "PPreflection::detail::basic_namespace<PPreflection::tags::global>{}"
		   ";\n";
}

const PPreflector::descriptor*
PPreflector::global_namespace::get_parent(void*) const
{
	return nullptr;
}
