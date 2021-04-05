#pragma once
#include "pragma_push.hpp"
#include "clang/AST/DeclCXX.h"
#include "pragma_pop.hpp"

#include "base_class.hpp"
#include "member_function.hpp"
#include "nested_descriptor.hpp"
#include "node_descriptor.hpp"
#include "static_function.hpp"

namespace PPreflector
{
	class Class : public node_descriptor<clang::RecordType, nested_descriptor<descriptor, descriptor>>
	{
		std::list<Class> nested_classes;
		std::list<base_class> base_classes;
		//std::list<constructor> constructors;
		//std::list<static_function> static_member_functions;
		//std::list<member_function> member_functions;

	public:
		Class(const clang::CXXRecordDecl& decl, const descriptor& parent);

		void print_name_header(llvm::raw_ostream& out) const override final;
		void print_name_own(llvm::raw_ostream& out) const override final;
		void print_name_foreign(llvm::raw_ostream& out) const override final;
		void print_metadata_object(llvm::raw_ostream&) const override final;
		void print_metadata_members(llvm::raw_ostream& out) const override final;
	};
}
