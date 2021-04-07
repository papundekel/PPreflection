#pragma once
#include "pragma_push.hpp"
#include "clang/AST/DeclCXX.h"
#include "pragma_pop.hpp"

#include "base_class.hpp"
#include "constructor.hpp"
#include "conversion_function.hpp"
#include "nested_descriptor.hpp"
#include "node_descriptor.hpp"
#include "non_conversion_member_function.hpp"
#include "static_member_function.hpp"

namespace PPreflector
{
	class Class : public node_descriptor<clang::RecordType, nested_descriptor<descriptor, descriptor>>
	{
		std::list<Class> nested_types;
		std::list<base_class> base_classes;
		std::list<constructor> constructors;
		std::list<static_member_function> static_member_functions;
		std::list<non_conversion_member_function> non_conversion_member_functions;
		std::list<conversion_function> conversion_functions;

	public:
		Class(const clang::CXXRecordDecl& decl, const descriptor& parent);

		void print_name_header(llvm::raw_ostream& out) const override final;
		void print_name_own(llvm::raw_ostream& out) const override final;
		void print_name_foreign(llvm::raw_ostream& out) const override final;
		void print_metadata_object(llvm::raw_ostream&) const override final;
		void print_metadata_members(llvm::raw_ostream& out) const override final;
	};
}
