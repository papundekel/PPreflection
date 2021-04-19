#pragma once
#include "pragma_push.hpp"
#include "clang/AST/Type.h"
#include "pragma_pop.hpp"

#include "node_descriptor.hpp"

namespace PPreflector
{
	class base_class : public node_descriptor<clang::Type, descriptor>
	{
	public:
		base_class(const clang::Type& t);

		void print_name_header(llvm::raw_ostream& out) const override final;
		void print_name_own(llvm::raw_ostream& out) const override final;
		void print_name_foreign(llvm::raw_ostream& out) const override final;

		void print_metadata_members(llvm::raw_ostream& out) const override final;
		void print_metadata_traits(llvm::raw_ostream& out) const override final;
		void print_metadata_object(llvm::raw_ostream& out) const override final;
	};
}
