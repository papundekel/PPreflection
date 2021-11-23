#pragma once
#include "PP/ref_wrap.hpp"

// clang-format off
#include "pragma_push.hpp"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "pragma_pop.hpp"
// clang-format on

#include "Class.hpp"
#include "global_namespace.hpp"
#include "non_global_namespace.hpp"

namespace PPreflector
{
	///
	/// @brief A basic implementation of an AST visitor. The visitor is
	/// responsible for processing each node of an AST.
	///
	class visitor : public clang::RecursiveASTVisitor<visitor>
	{
		// clang::ASTContext& context;
		global_namespace global;
		std::map<const clang::NamespaceDecl*,
		         PP::ref_wrap<non_global_namespace&>>
			map_namespaces;
		std::vector<PP::ref_wrap<const Class&>> classes;

	public:
		///
		/// @brief Constructs a new visitor.
		///
		/// @param ci A reference to the compiler.
		///
		explicit visitor(clang::CompilerInstance& ci);

		///
		/// @brief Processes a declaration.
		///
		/// @param declaration A pointer to the declaration.
		/// @return true Success.
		/// @return false Failure.
		///
		bool VisitDecl(clang::Decl* declaration);

		///
		/// @brief Prints the metadata.
		///
		/// @param out
		///
		void print(llvm::raw_ostream& out) const;

		///
		/// @brief Frees all temporary resources.
		///
		void clear_temps();

		///
		/// @brief Removes unwanted entities from the registry.
		///
		void remove_unwanted();

	private:
		Namespace* get_namespace_parent(
			clang::DeclContext& declaration_context);
		void register_namespace(clang::NamespaceDecl& child_declaration);

		static llvm::raw_ostream& print_name(llvm::raw_ostream& out,
		                                     const clang::NamedDecl& d);
		static bool is_reserved(const clang::NamedDecl& d);
	};
}
