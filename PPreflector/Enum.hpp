#pragma once
#include <vector>

// clang-format off
#include "pragma_push.hpp"
#include "clang/AST/Type.h"
#include "pragma_pop.hpp"
// clang-format on

#include "descriptor.hpp"
#include "enum_value.hpp"
#include "nested_descriptor.hpp"
#include "node_descriptor.hpp"

namespace PPreflector
{
	class Enum
		: public node_descriptor<clang::EnumType,
								 nested_descriptor<descriptor, descriptor>>
	{
		std::vector<enum_value> enum_values;

	public:
		Enum(const clang::EnumDecl& decl, const descriptor& parent);

		void print_name_header(llvm::raw_ostream& out) const override final;
		void print_name_own(llvm::raw_ostream& out) const override final;
		void print_name_foreign(llvm::raw_ostream& out) const override final;

		void print_metadata_members(
			llvm::raw_ostream& out) const override final;
		void print_metadata_traits(llvm::raw_ostream& out) const override final;
		void print_metadata_object(llvm::raw_ostream& out) const override final;
	};
}
