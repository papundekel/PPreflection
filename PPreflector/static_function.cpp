#include "static_function.hpp"

#include "pragma_push.hpp"
#include "clang/AST/PrettyPrinter.h"
#include "clang/Basic/LangOptions.h"
#include "pragma_pop.hpp"

#include "for_each_with_delimiters.hpp"
#include "printers.hpp"

void PPreflector::static_function::print_name_header(llvm::raw_ostream& out) const
{
	out << PPREFLECTOR_MEMBER_PRINT(print_qualified_name, *this) << '(' << PPREFLECTOR_MEMBER_PRINT(print_parameter_types, *this) << ")";
}

void PPreflector::static_function::print_name_own(llvm::raw_ostream& out) const
{
	out << printer_value_t(PPREFLECTOR_MEMBER_PRINT(print_name_foreign, *this));
}

void PPreflector::static_function::print_name_foreign(llvm::raw_ostream& out) const
{
	out << "PPreflection::overload_caster<" << PPREFLECTOR_MEMBER_PRINT(print_parameter_types, *this) << ">(::" << PPREFLECTOR_MEMBER_PRINT(print_qualified_name, *this) << ")";
}

void PPreflector::static_function::print_metadata_members(llvm::raw_ostream& out) const
{
	out << PPREFLECTOR_MEMBER_PRINT(print_metadata_name, *this) << "\n"
		<< PPREFLECTOR_MEMBER_PRINT(print_metadata_parent, *this) << "\n";
}
