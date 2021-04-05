#pragma once
#include "pragma_push.hpp"
#include "clang/AST/Decl.h"
#include "pragma_pop.hpp"

#include "Namespace.h"
#include "nested_descriptor.hpp"
#include "node_descriptor.hpp"

namespace PPreflector
{
	class non_global_namespace : public node_descriptor<clang::NamespaceDecl, nested_descriptor<Namespace, Namespace>>
	{
	public:
		non_global_namespace(PP::size_t depth, const clang::NamespaceDecl& decl, const Namespace& parent);

		bool is_std() const;

	private:
		void print_name_parent(llvm::raw_ostream& out) const override final;

		void print_unscoped_name(llvm::raw_ostream& out) const override final;
		void print_scoped_name_parent(llvm::raw_ostream& out) const override final;
		void print_scoped_name_as_parent(llvm::raw_ostream& out) const override final;

		void print_metadata_object(llvm::raw_ostream& out) const override final;
	};
}
