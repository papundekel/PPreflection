#pragma once
// clang-format off
#include "pragma_push.hpp"
#include "clang/AST/Decl.h"
#include "pragma_pop.hpp"
// clang-format on

#include "function.hpp"

namespace PPreflector
{
	class static_function : public function<clang::FunctionDecl>
	{
	public:
		using function<clang::FunctionDecl>::function;

		void print_name_header(llvm::raw_ostream& out) const override final;
		void print_name_own(llvm::raw_ostream& out) const override final;
		void print_name_foreign(llvm::raw_ostream& out) const override final;

		void print_metadata_traits(llvm::raw_ostream& out) const override final;
	};
}
