#pragma once
#include "pragma_push.hpp"
#include "clang/AST/Decl.h"
#include "pragma_pop.hpp"

#include "descriptor.hpp"
#include "nested_descriptor.hpp"
#include "node_descriptor.hpp"

namespace PPreflector
{	
	class member_function : public node_descriptor<clang::FunctionDecl, nested_descriptor<descriptor, descriptor>>
	{
	public:
		member_function(const clang::FunctionDecl& decl, const descriptor& parent);

		void print_name_header(llvm::raw_ostream& out) const override final;
		void print_name_own(llvm::raw_ostream& out) const override final;
		void print_name_foreign(llvm::raw_ostream& out) const override final;
		void print_parameter_types(llvm::raw_ostream& out) const;
		void print_metadata_members(llvm::raw_ostream& out) const override final;
	};
}
