#pragma once
#include "pragma_push.hpp"
#include "clang/AST/Type.h"
#include "pragma_pop.hpp"

#include "Namespace.hpp"
#include "node_descriptor.hpp"
#include "Class.hpp"

namespace PPreflector
{
	class Enum : public node_descriptor<clang::EnumType>
	{
		const descriptor& parent;

	public:
		Enum(const clang::EnumType& type, const descriptor& parent);

		void print_metadata_name_header(llvm::raw_ostream& out) const override final;
		void print_metadata_name_own(llvm::raw_ostream& out) const override final;
		void print_metadata_name_foreign(llvm::raw_ostream& out) const override final;
		void print_metadata_implementation(llvm::raw_ostream& out) const override final;
	};
}
