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
	///
	/// @brief Represents an enum.
	///
	class Enum
		: public node_descriptor<clang::EnumType,
	                             nested_descriptor<descriptor, descriptor>>
	{
		std::vector<enum_value> enum_values;

	public:
		///
		/// @brief Constructs a new enum descriptor.
		///
		/// @param decl A reference to the AST declaration of the enum.
		/// @param parent A reference to the desriptor of the parent entity.
		///
		Enum(const clang::EnumDecl& decl, const descriptor& parent);

		///
		/// @brief @see descriptor::print_name_header.
		///
		void print_name_header(llvm::raw_ostream& out) const override final;
		///
		/// @brief @see descriptor::print_name_own.
		///
		void print_name_own(llvm::raw_ostream& out) const override final;
		///
		/// @brief @see descriptor::print_name_foreign.
		///
		void print_name_foreign(llvm::raw_ostream& out) const override final;

		///
		/// @brief @see descriptor::print_metadata_members.
		///
		void print_metadata_members(
			llvm::raw_ostream& out) const override final;
		///
		/// @brief @see descriptor::print_metadata_traits.
		///
		void print_metadata_traits(llvm::raw_ostream& out) const override final;
		///
		/// @brief @see descriptor::print_metadata_object.
		///
		void print_metadata_object(llvm::raw_ostream&) const override final;
	};
}
