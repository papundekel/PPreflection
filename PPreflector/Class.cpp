#include "Class.hpp"

#include "PP/push_back_iterator.hpp"
#include "PP/view_chain.hpp"

PPreflector::Class::Class(const clang::CXXRecordDecl& decl, const descriptor& parent)
	: node_descriptor<clang::RecordType, nested_descriptor<descriptor, descriptor>>(*clang::dyn_cast_or_null<clang::RecordType>(decl.getTypeForDecl()), parent)
	, nested_classes()
	, base_classes()
	//, constructors()
	//, static_member_functions()
	//, member_functions()
{
	PP::view_copy(PP::push_back_iterator(base_classes) ^ PP::unbounded, decl.bases() | PP::transform([]
		(const clang::CXXBaseSpecifier& base) -> auto&
		{
			return *base.getType().getTypePtr();
		}));
}

void PPreflector::Class::print_name_header(llvm::raw_ostream& out) const
{
	out << PPREFLECTOR_MEMBER_PRINT(print_qualified_name, *this);
}

void PPreflector::Class::print_name_own(llvm::raw_ostream& out) const
{
	out << "::" << PPREFLECTOR_MEMBER_PRINT(print_name_header, *this);
}

void PPreflector::Class::print_name_foreign(llvm::raw_ostream& out) const
{
	print_name_own(out);
}

void PPreflector::Class::print_metadata_object(llvm::raw_ostream&) const
{
	// print nothing
}

void PPreflector::Class::print_metadata_members(llvm::raw_ostream& out) const
{
	print_metadata_name(out);
	print_metadata_parent(out);

	print_members(out, nested_classes, "nested_classes", printer_type_tuple);
	print_members(out, base_classes, "base_classes", printer_type_tuple);
	//print_members(out, constructors, "constructors", printer_make_tuple);
	//print_members(out, static_member_functions, "static_member_functions", printer_value_tuple);
	//print_members(out, member_functions, "member_functions", printer_value_tuple);

	for (const descriptor& d : PP::view_chain(
			as_descriptors_view(nested_classes))/* ^
			as_descriptors_view(constructors) ^
			as_descriptors_view(static_member_functions) ^
			as_descriptors_view(member_functions)*/)
		d.print_metadata(out);
}
