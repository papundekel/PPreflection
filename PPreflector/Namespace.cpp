#include "Namespace.hpp"

#include "PP/transform_view.hpp"
#include "PP/view_chain.hpp"

#include "for_each_with_delimiters.hpp"
#include "printers.hpp"

PPreflector::Namespace::Namespace(PP::size_t depth)
	: descriptor()
	, depth(depth)
	, namespaces()
	, functions()
	, enums()
	, classes()
{}

void PPreflector::Namespace::print_name_header(llvm::raw_ostream& out) const
{
	print_scoped_name_parent(out);
	print_unscoped_name(out);
}
void PPreflector::Namespace::print_name_own(llvm::raw_ostream& out) const
{
	print_name_parent(out);
	out << "::";
	print_name(out);
}
void PPreflector::Namespace::print_name_foreign(llvm::raw_ostream& out) const
{
	print_name_own(out);
}

PPreflector::non_global_namespace& PPreflector::Namespace::add(clang::NamespaceDecl& n)
{
	return namespaces.emplace_back(depth + 1, n, *this);;
}

PPreflector::namespace_function& PPreflector::Namespace::add(clang::FunctionDecl& f)
{
	return functions.emplace_back(f, *this);
}

PPreflector::Enum& PPreflector::Namespace::add(clang::EnumDecl& e)
{
	return enums.emplace_back(e, *this);
}

PPreflector::Class& PPreflector::Namespace::add(clang::CXXRecordDecl& c)
{
	return classes.emplace_back(c, *this);
}

void PPreflector::Namespace::remove_std()
{
	namespaces.remove_if([](const non_global_namespace& n) { return n.is_std(); });
}

void PPreflector::Namespace::print_tabs(llvm::raw_ostream& out) const
{
	for (PP::size_t i = 0; i != depth + 1; ++i)
		out.write('\t');
}

void PPreflector::Namespace::print_layout(llvm::raw_ostream& out) const
{
	out << PPREFLECTOR_MEMBER_PRINT(print_tabs, *this) << "struct " << PPREFLECTOR_MEMBER_PRINT(print_name, *this);

	if (namespaces.empty())
	{
		out << ";\n";
	}
	else
	{
		out << "\n"
			<< PPREFLECTOR_MEMBER_PRINT(print_tabs, *this) << "{\n";

		for (const auto& n : namespaces)
			out << PPREFLECTOR_MEMBER_PRINT(print_layout, n);

		out << PPREFLECTOR_MEMBER_PRINT(print_tabs, *this) << "};\n";
	}
}

void PPreflector::Namespace::print_metadata_members(llvm::raw_ostream& out) const
{
	for (const descriptor& d : PP::view_chain(
			as_descriptors_view(functions)) ^
			as_descriptors_view(enums) ^
			as_descriptors_view(classes) ^
			as_descriptors_view(namespaces))
		d.print_metadata(out);
}

void PPreflector::Namespace::print_metadata_traits(llvm::raw_ostream& out) const
{
	print_members<"functions"_str>(out, functions, printer_value_tuple) << "\n";
	print_members<"types"_str>(out, PP::view_chain(as_descriptors_view(enums)) ^ as_descriptors_view(classes), printer_type_tuple) << "\n";
	print_members<"namespaces"_str>(out, namespaces, printer_type_tuple) << "\n";
}
