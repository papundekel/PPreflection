#include "static_function.hpp"

#include "pragma_push.hpp"
#include "clang/AST/PrettyPrinter.h"
#include "clang/Basic/LangOptions.h"
#include "pragma_pop.hpp"

#include "for_each_with_delimiters.hpp"
#include "printers.hpp"
#include "printing_policy.hpp"
#include "strings.hpp"

PPreflector::static_function::static_function(const clang::FunctionDecl& decl, const descriptor& parent)
	: node_descriptor<clang::FunctionDecl, nested_descriptor<descriptor, descriptor>>(decl, parent)
{}

void PPreflector::static_function::print_name_header(llvm::raw_ostream& out) const
{
	out << PPREFLECTOR_MEMBER_PRINT(print_qualified_name, *this) << '(' << PPREFLECTOR_MEMBER_PRINT(print_parameter_types, *this) << ")";
}

void PPreflector::static_function::print_name_own(llvm::raw_ostream& out) const
{
	out << "PP::value_t<" << PPREFLECTOR_MEMBER_PRINT(print_name_foreign, *this) << '>';
}

void PPreflector::static_function::print_name_foreign(llvm::raw_ostream& out) const
{
	out << "PPreflection::overload_caster<" << PPREFLECTOR_MEMBER_PRINT(print_parameter_types, *this) << ">(::" << PPREFLECTOR_MEMBER_PRINT(print_qualified_name, *this) << ")";
}

void PPreflector::static_function::print_parameter_types(llvm::raw_ostream& out) const
{
	for_each_with_delimiters([&out]
		(auto* parameter)
		{
			print_parameter_type(out, parameter);
		}, [&out]
		()
		{
			out << ", ";
		}, get_node().parameters());
}

void PPreflector::static_function::print_metadata_object(llvm::raw_ostream& out) const
{
	out << metadata_prefix << PPREFLECTOR_MEMBER_PRINT(print_name_own, *this) << "> = PPreflection::detail::basic_namespace_function<" << PPREFLECTOR_MEMBER_PRINT(print_name_foreign, *this) << ">{};";
}

void PPreflector::static_function::print_metadata_members(llvm::raw_ostream& out) const
{
	print_metadata_name(out);
	print_metadata_parent(out);
}

void PPreflector::static_function::print_parameter_type(llvm::raw_ostream& out, clang::ParmVarDecl* parameter)
{
	parameter->getType().print(out, printing_policy);
}
