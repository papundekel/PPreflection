#pragma once
#include "pragma_push.hpp"
#include "clang/AST/Decl.h"
#include "pragma_pop.hpp"

#include "descriptor.hpp"
#include "node_descriptor.hpp"

namespace PPreflector
{
	class namespace_function : public node_descriptor<clang::FunctionDecl>
	{
		const descriptor& parent;

	public:
		namespace_function(const clang::FunctionDecl& decl, const descriptor& parent);

		void print_metadata_name_header(llvm::raw_ostream& out) const override final;
		void print_metadata_name_own(llvm::raw_ostream& out) const override final;
		void print_metadata_name_foreign(llvm::raw_ostream& out) const override final;
		void print_parameter_types(llvm::raw_ostream& out) const;
		void print_metadata_implementation(llvm::raw_ostream& out) const override final;

	private:
		static void print_parameter_type(llvm::raw_ostream& out, clang::ParmVarDecl* parameter);
	};
}
