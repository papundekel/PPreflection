#include "namespace_function.hpp"

#include "pragma_push.hpp"
#include "clang/AST/PrettyPrinter.h"
#include "clang/Basic/LangOptions.h"
#include "pragma_pop.hpp"

#include "for_each_with_delimiters.hpp"
#include "print_wrap.hpp"
#include "printing_policy.hpp"
#include "strings.hpp"

PPreflector::namespace_function::namespace_function(const clang::FunctionDecl& decl, const descriptor& parent)
	: node_descriptor<clang::FunctionDecl, nested_descriptor<descriptor, descriptor>>(decl, parent)
{}

void PPreflector::namespace_function::print_name_header(llvm::raw_ostream& out) const
{
	out << PPREFLECTOR_PW(print_qualified_name, *this) << '(' << PPREFLECTOR_PW(print_parameter_types, *this) << ")";
}

void PPreflector::namespace_function::print_name_own(llvm::raw_ostream& out) const
{
	out << "PP::value_t<" << PPREFLECTOR_PW(print_name_foreign, *this) << '>';
}

void PPreflector::namespace_function::print_name_foreign(llvm::raw_ostream& out) const
{
	out << "PPreflection::overload_caster<" << PPREFLECTOR_PW(print_parameter_types, *this) << ">(::" << PPREFLECTOR_PW(print_qualified_name, *this) << ")";
}

void PPreflector::namespace_function::print_parameter_types(llvm::raw_ostream& out) const
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

void PPreflector::namespace_function::print_metadata_implementation(llvm::raw_ostream& out) const
{
	out << metadata_prefix << PPREFLECTOR_PW(print_name_own, *this) << "> = PPreflection::detail::basic_namespace_function<" << PPREFLECTOR_PW(print_name_foreign, *this) << ">{};\n";
	print_metadata_name(out);
	print_metadata_parent(out);
}

void PPreflector::namespace_function::print_parameter_type(llvm::raw_ostream& out, clang::ParmVarDecl* parameter)
{
	parameter->getType().print(out, printing_policy);
}
