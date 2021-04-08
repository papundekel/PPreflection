#pragma once
#include "PP/ref_wrap.hpp"

#include "pragma_push.hpp"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "pragma_pop.hpp"

#include "global_namespace.hpp"
#include "non_global_namespace.hpp"

namespace PPreflector
{
	class visitor : public clang::RecursiveASTVisitor<visitor>
	{
		clang::ASTContext& context;
		global_namespace global;
		std::map<const clang::NamespaceDecl*, PP::ref_wrap<non_global_namespace&>> map_namespaces;

	public:
		explicit visitor(clang::CompilerInstance& ci);

		bool VisitDecl(clang::Decl* declaration);
		void print(llvm::raw_ostream& out) const;
		void clear_temps();
		void remove_unwanted();

	private:
		Namespace* get_namespace_parent(clang::DeclContext& declaration_context);
		void register_namespace(clang::NamespaceDecl& child_declaration);

		static llvm::raw_ostream& print_name(llvm::raw_ostream& out, const clang::NamedDecl& d);
		static bool is_reserved(const clang::NamedDecl& d);
	};
}
