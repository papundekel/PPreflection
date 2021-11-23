#pragma once
// clang-format off
#include "pragma_push.hpp"
#include "clang/AST/Decl.h"
#include "pragma_pop.hpp"
// clang-format on

#include "descriptor.hpp"
#include "node_descriptor.hpp"

namespace PPreflector
{
	///
	/// @brief Represents an enum value.
	///
	class enum_value
		: public node_descriptor<clang::EnumConstantDecl, descriptor>
	{
	public:
		///
		/// @brief Constructs a new enum value descriptor.
		///
		/// @param decl A reference to the declaration of the enum value.
		///
		enum_value(const clang::EnumConstantDecl& decl);

		void print_name_header(llvm::raw_ostream& out) const override final;
		void print_name_own(llvm::raw_ostream& out) const override final;
		void print_name_foreign(llvm::raw_ostream& out) const override final;

		void print_metadata_members(
			llvm::raw_ostream& out) const override final;
		void print_metadata_traits(llvm::raw_ostream& out) const override final;
		void print_metadata_object(llvm::raw_ostream& out) const override final;

		const descriptor* get_parent(void* = nullptr) const override final;
	};
}
