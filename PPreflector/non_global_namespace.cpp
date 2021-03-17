#include "non_global_namespace.hpp"

#include "print_wrap.hpp"
#include "strings.hpp"

void PPreflector::non_global_namespace::print_name_parent(llvm::raw_ostream& out) const
{
	parent.print_name_full(out);
}
void PPreflector::non_global_namespace::print_name_simple_no_prefix(llvm::raw_ostream& out) const
{
	print_name_simple(out);
}
void PPreflector::non_global_namespace::print_name_simple(llvm::raw_ostream& out) const
{
	out << PPREFLECTOR_PW(print_name_simple_no_prefix, parent) << "::" << PPREFLECTOR_PW(print_name, *this);
}
void PPreflector::non_global_namespace::print_preamble(llvm::raw_ostream& out) const
{
	out << metadata_prefix << PPREFLECTOR_PW(print_name_full, *this) << "> = PPreflection::detail::basic_namespace<" << PPREFLECTOR_PW(print_name_full, *this) << ">{};\n";		
	out << metadata_prefix << tags_namespace_name << "name<"   << PPREFLECTOR_PW(print_name_full, *this) << ">> = \"" << PPREFLECTOR_PW(print_name, *this) << "\"_sv;\n";
	out << metadata_prefix << tags_namespace_name << "parent<" << PPREFLECTOR_PW(print_name_full, *this) << ">> = PP::type<" << PPREFLECTOR_PW(print_name_full, parent) << ">;\n";
}

PPreflector::non_global_namespace::non_global_namespace(PP::size_t depth, const clang::NamespaceDecl& decl, const Namespace& parent)
	: node_descriptor<clang::NamespaceDecl, Namespace>(decl, depth)
	, parent(parent)
{}

bool PPreflector::non_global_namespace::is_std() const
{
	return get_node().isStdNamespace();
}
