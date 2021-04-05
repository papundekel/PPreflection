#include "descriptor.hpp"

#include "printers.hpp"
#include "strings.hpp"

PPreflector::descriptor::~descriptor()
{}

const PPreflector::descriptor* PPreflector::descriptor::get_parent(void*) const
{
	return nullptr;
}

void PPreflector::descriptor::print_metadata(llvm::raw_ostream& out) const
{
	out <<	"\n"
			"// ::" << PPREFLECTOR_MEMBER_PRINT(print_name_header, *this) << "\n"
		<<	PPREFLECTOR_MEMBER_PRINT(print_metadata_object, *this) << "\n"
		<<	PPREFLECTOR_MEMBER_PRINT(print_metadata_members, *this);
}

void PPreflector::descriptor::print_metadata_name(llvm::raw_ostream& out) const
{
	out << metadata_prefix << tags_namespace_name << "name<" << PPREFLECTOR_MEMBER_PRINT(print_name_own, *this) << ">> = \"" << PPREFLECTOR_MEMBER_PRINT(print_name, *this) << "\"_sv;\n";
}

void PPreflector::descriptor::print_metadata_parent(llvm::raw_ostream& out) const
{
	out << metadata_prefix << tags_namespace_name << "parent<" << PPREFLECTOR_MEMBER_PRINT(print_name_own, *this) << ">> = PP::type<" << PPREFLECTOR_MEMBER_PRINT(print_name_foreign, *get_parent()) << ">;\n";
}
