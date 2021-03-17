#pragma once
#include "pragma_push.hpp"
#include "clang/AST/Decl.h"
#include "pragma_pop.hpp"

#include "Namespace.h"
#include "node_descriptor.hpp"

namespace PPreflector
{
	class non_global_namespace : public node_descriptor<clang::NamespaceDecl, Namespace>	
	{
		const Namespace& parent;

	public:
		non_global_namespace(PP::size_t depth, const clang::NamespaceDecl& decl, const Namespace& parent);

		bool is_std() const;

	private:
		void print_name_parent(llvm::raw_ostream& out) const override final;
		void print_name_simple_no_prefix(llvm::raw_ostream& out) const override final;
		void print_name_simple(llvm::raw_ostream& out) const override final;
		void print_preamble(llvm::raw_ostream& out) const override final;
	};
}
