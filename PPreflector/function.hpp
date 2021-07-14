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

	template <typename FDecl>
	requires PP::concepts::derived_from<FDecl, clang::FunctionDecl>
	class function
		: public node_descriptor<FDecl,
	                             nested_descriptor<descriptor, descriptor>>
	{
	public:
		function(const FDecl& decl, const descriptor& parent)
			: node_descriptor<FDecl, nested_descriptor<descriptor, descriptor>>(
				  decl,
				  parent)
		{}

		void print_metadata_members(llvm::raw_ostream&) const override final
		{
			// print nothing
		}

	protected:
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
