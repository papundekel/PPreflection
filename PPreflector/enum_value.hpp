#pragma once
#include "pragma_push.hpp"
#include "clang/AST/Decl.h"
#include "pragma_pop.hpp"

#include "descriptor.hpp"
#include "node_descriptor.hpp"

namespace PPreflector
{
	class enum_value : public node_descriptor<clang::EnumConstantDecl, descriptor>
	{
	public:
		enum_value(const clang::EnumConstantDecl& decl);

		void print_name_header(llvm::raw_ostream& out) const override final;
		void print_name_own(llvm::raw_ostream& out) const override final;
		void print_name_foreign(llvm::raw_ostream& out) const override final;
		void print_metadata_implementation(llvm::raw_ostream& out) const override final;
		const descriptor* get_parent(void* = nullptr) const override final;
	};
}
