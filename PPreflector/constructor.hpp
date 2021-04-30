#pragma once
#include "pragma_pop.hpp"
#include "pragma_push.hpp"
#include "clang/AST/DeclCXX.h"

#include "function.hpp"

namespace PPreflector
{
	class constructor : public function<clang::CXXConstructorDecl>
	{
	public:
		using function<clang::CXXConstructorDecl>::function;

		void print_name_header(llvm::raw_ostream& out) const override final;
		void print_name_own(llvm::raw_ostream& out) const override final;
		void print_name_foreign(llvm::raw_ostream& out) const override final;

		void print_metadata_traits(llvm::raw_ostream&) const override final;
		void print_metadata_object(llvm::raw_ostream&) const override final;

		void print_id(llvm::raw_ostream& out) const;
	};
}
