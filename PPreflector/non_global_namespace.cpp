#include "non_global_namespace.hpp"

#include "printers.hpp"

PPreflector::non_global_namespace::non_global_namespace(
	PP::size_t					depth,
	const clang::NamespaceDecl& decl,
	const Namespace&			parent)
	: node_descriptor<clang::NamespaceDecl,
					  nested_descriptor<Namespace, Namespace>>(decl,
															   parent,
															   depth)
{}

bool
PPreflector::non_global_namespace::is_std() const
{
	return get_node().isStdNamespace();
}

void
PPreflector::non_global_namespace::print_name_parent(
	llvm::raw_ostream& out) const
{
	get_parent().print_name_own(out);
}

void
PPreflector::non_global_namespace::print_unscoped_name(
	llvm::raw_ostream& out) const
{
	print_name(out);
}

void
PPreflector::non_global_namespace::print_scoped_name_parent(
	llvm::raw_ostream& out) const
{
	get_parent().print_scoped_name_as_parent(out);
}

void
PPreflector::non_global_namespace::print_scoped_name_as_parent(
	llvm::raw_ostream& out) const
{
	out << PPREFLECTOR_MEMBER_PRINT(print_scoped_name_as_parent, get_parent())
		<< PPREFLECTOR_MEMBER_PRINT(print_unscoped_name, *this) << "::";
}

void
PPreflector::non_global_namespace::print_metadata_traits(
	llvm::raw_ostream& out) const
{
	out << PPREFLECTOR_MEMBER_PRINT(print_metadata_name, *this) << "\n"
		<< PPREFLECTOR_MEMBER_PRINT(print_metadata_parent, *this) << "\n"
		<< PPREFLECTOR_MEMBER_PRINT(Namespace::print_metadata_traits, *this);
}

void
PPreflector::non_global_namespace::print_metadata_object(
	llvm::raw_ostream& out) const
{
	out << printer_metadata(PPREFLECTOR_MEMBER_PRINT(print_name_own, *this))
		<< "PPreflection::detail::basic_namespace<"
		<< PPREFLECTOR_MEMBER_PRINT(print_name_own, *this) << ">{};\n";
}
