#pragma once
// clang-format off
#include "pragma_push.hpp"
#include "clang/AST/Decl.h"
#include "pragma_pop.hpp"
// clang-format on

#include "Namespace.h"
#include "nested_descriptor.hpp"
#include "node_descriptor.hpp"

namespace PPreflector
{
	///
	/// @brief Represents a non-global namespace.
	///
	class non_global_namespace
		: public node_descriptor<clang::NamespaceDecl,
	                             nested_descriptor<Namespace, Namespace>>
	{
	public:
		///
		/// @brief Construct a descriptor of a non-global namespace.
		///
		/// @param depth The number of parent namespaces.
		/// @param decl The declaration from the AST that represents the
		/// namespace's first declaration.
		/// @param parent A reference to the descriptor of the parent namespace.
		///
		non_global_namespace(PP::size_t depth,
		                     const clang::NamespaceDecl& decl,
		                     const Namespace& parent);

		///
		/// @brief Checks if this descriptor refers to the std namespace.
		///
		/// @return true This refers to the std namespace.
		/// @return false This does not refer to the std namespace.
		///
		bool is_std() const;

	private:
		void print_name_parent(llvm::raw_ostream& out) const override final;

		void print_layout_name(llvm::raw_ostream& out) const override final;

		void print_unscoped_name(llvm::raw_ostream& out) const override final;
		void print_scoped_name_parent(
			llvm::raw_ostream& out) const override final;
		void print_scoped_name_as_parent(
			llvm::raw_ostream& out) const override final;

		void print_metadata_traits(llvm::raw_ostream& out) const override final;
		void print_metadata_object(llvm::raw_ostream& out) const override final;
	};
}
