#include "global_namespace.hpp"

#include "Class.hpp"
#include "Enum.hpp"
#include "non_global_namespace.hpp"

PPreflector::global_namespace::global_namespace()
	: Namespace(0)
{}

void PPreflector::global_namespace::print_name_parent(
	llvm::raw_ostream& out) const
{
	out << "tags";
}

void PPreflector::global_namespace::print_qualified_name(
	llvm::raw_ostream&) const
{
	// print nothing
}

void PPreflector::global_namespace::print_name(llvm::raw_ostream& out) const
{
	out << "global<X()>";
}

void PPreflector::global_namespace::print_layout_name(
	llvm::raw_ostream& out) const
{
	out << "global<detail::X()>";
}

void PPreflector::global_namespace::print_unscoped_name(
	llvm::raw_ostream&) const
{
	// print nothing
}

void PPreflector::global_namespace::print_scoped_name_parent(
	llvm::raw_ostream&) const
{
	// print nothing
}

void PPreflector::global_namespace::print_scoped_name_as_parent(
	llvm::raw_ostream&) const
{
	// print nothing
}

void PPreflector::global_namespace::print_metadata_object(
	llvm::raw_ostream& out) const
{
	// clang-format off
	out << "\ttemplate <> constexpr inline auto metadata<X(), tags::global<X()>> = basic_namespace<tags::global<X()>>{};";
	// clang-format on
}

const PPreflector::descriptor* PPreflector::global_namespace::get_parent(
	void*) const
{
	return nullptr;
}
