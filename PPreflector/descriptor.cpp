#include "descriptor.hpp"

#include "printers.hpp"

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
		<<	PPREFLECTOR_MEMBER_PRINT(print_metadata_object, *this)
		<<	PPREFLECTOR_MEMBER_PRINT(print_metadata_members, *this);
}

void PPreflector::descriptor::print_metadata_name(llvm::raw_ostream& out) const
{
	out << printer_metadata(metadata_tag_printer<"name"_str>(PPREFLECTOR_MEMBER_PRINT(print_name_own, *this))) << printer_sv(PPREFLECTOR_MEMBER_PRINT(print_name, *this)) << ";";
}

void PPreflector::descriptor::print_metadata_parent(llvm::raw_ostream& out) const
{
	out << printer_metadata(metadata_tag_printer<"parent"_str>(PPREFLECTOR_MEMBER_PRINT(print_name_own, *this))) << printer_type(PPREFLECTOR_MEMBER_PRINT(print_name_foreign, *get_parent())) << ";";
}
