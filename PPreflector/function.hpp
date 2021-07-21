#pragma once
#include "PP/concepts/derived_from.hpp"

// clang-format off
#include "pragma_push.hpp"
#include "clang/AST/Decl.h"
#include "pragma_pop.hpp"
// clang-format on

#include "descriptor.hpp"
#include "for_each_with_delimiters.hpp"
#include "nested_descriptor.hpp"
#include "node_descriptor.hpp"
#include "printing_policy.hpp"

namespace PPreflector
{
	///
	/// @brief Represents a function.
	///
	/// @tparam FDecl The type of the AST function declaration.
	///
	template <typename FDecl>
	requires PP::concepts::derived_from<FDecl, clang::FunctionDecl>
	class function
		: public node_descriptor<FDecl,
	                             nested_descriptor<descriptor, descriptor>>
	{
	public:
		///
		/// @brief Constructs a new function descriptor.
		///
		/// @param decl A reference to the function declaration.
		/// @param parent A reference to the parent entity descriptor.
		///
		function(const FDecl& decl, const descriptor& parent)
			: node_descriptor<FDecl, nested_descriptor<descriptor, descriptor>>(
				  decl,
				  parent)
		{}

		///
		/// @brief @see descriptor::print_metadata_members.
		///
		void print_metadata_members(llvm::raw_ostream&) const override final
		{
			// print nothing
		}

	protected:
		///
		/// @brief Prints the parameter types delimited with a comma.
		///
		/// @param out
		///
		virtual void print_parameter_types(llvm::raw_ostream& out) const
		{
			for_each_with_delimiters(
				[&out](auto* parameter)
				{
					parameter->getType().print(out, printing_policy);
				},
				[&out]()
				{
					out << ", ";
				},
				this->get_node().parameters());
		}

		///
		/// @brief Prints the parameter types with a leading comma.
		///
		/// @param out
		///
		virtual void print_parameter_types_leading_comma(
			llvm::raw_ostream& out) const
		{
			for (const auto* parameter : this->get_node().parameters())
			{
				out << ", ";
				parameter->getType().print(out, printing_policy);
			}
		}
	};
}
