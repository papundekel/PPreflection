#pragma once
#include <list>
#include <vector>

// clang-format off
#include "pragma_push.hpp"
#include "clang/AST/DeclCXX.h"
#include "pragma_pop.hpp"
// clang-format on

#include "base_class.hpp"
#include "constructor.hpp"
#include "conversion_function.hpp"
#include "nested_descriptor.hpp"
#include "node_descriptor.hpp"
#include "non_conversion_member_function.hpp"
#include "static_member_function.hpp"

namespace PPreflector
{
	///
	/// @brief Represents a non-union class.
	///
	class Class
		: public node_descriptor<clang::RecordType,
	                             nested_descriptor<descriptor, descriptor>>
	{
		std::list<Class> nested_types;
		std::vector<base_class> base_classes;
		std::vector<constructor> constructors;
		std::vector<static_member_function> static_member_functions;
		std::vector<non_conversion_member_function>
			non_conversion_member_functions;
		std::vector<conversion_function> conversion_functions;

	public:
		///
		/// @brief Construct a new non-union class descriptor.
		///
		/// @param decl A reference to the class declaration.
		/// @param parent A reference to the parent entity descriptor.
		///
		Class(const clang::CXXRecordDecl& decl, const descriptor& parent);

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
