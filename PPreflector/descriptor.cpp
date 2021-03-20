#include "descriptor.hpp"

#include "print_wrap.hpp"
#include "strings.hpp"

PPreflector::descriptor::~descriptor()
{}

void PPreflector::descriptor::print_metadata(llvm::raw_ostream& out) const
{
	out <<	"\n"
			"// ::" << PPREFLECTOR_PW(print_name_header, *this) << "\n"
		<<	PPREFLECTOR_PW(print_metadata_implementation, *this);
}

void PPreflector::descriptor::print_metadata_name(llvm::raw_ostream& out) const
{
	out << metadata_prefix << tags_namespace_name << "name<" << PPREFLECTOR_PW(print_name_own, *this) << ">> = \"" << PPREFLECTOR_PW(print_name, *this) << "\"_sv;\n";
}

void PPreflector::descriptor::print_metadata_parent(llvm::raw_ostream& out) const
{
	out << metadata_prefix << tags_namespace_name << "parent<" << PPREFLECTOR_PW(print_name_own, *this) << ">> = PP::type<" << PPREFLECTOR_PW(print_name_foreign, *get_parent()) << ">;\n";
}
