#pragma once
#include "PP/concepts/derived_from.hpp"

// clang-format off
#include "pragma_push.hpp"
#include "clang/AST/Decl.h"
#include "clang/AST/PrettyPrinter.h"
#include "pragma_pop.hpp"
// clang-format on

#include "descriptor.hpp"
#include "printing_policy.hpp"

namespace PPreflector
{
	///
	/// @brief Represents an entity, which has an associated AST node.
	///
	/// @tparam Node AST node type representing a declaration of this entity.
	/// @tparam Descriptor The base descriptor class.
	///
	template <typename Node, typename Descriptor = descriptor>
	requires PP::concepts::derived_from<Descriptor, descriptor>
	class node_descriptor : public Descriptor
	{
		const Node& node;

	public:
		///
		/// @brief Constructs a new node descriptor.
		///
		/// @param node A reference to the AST node associated with this entity.
		/// @param args Arguments for the Descriptor constructor.
		///
		explicit node_descriptor(const Node& node, auto&&... args)
			: Descriptor(PP_F(args)...)
			, node(node)
		{}

		void print_qualified_name(llvm::raw_ostream& out) const override final
		{
			if constexpr (PP::concepts::derived_from<Node, clang::NamedDecl>)
				node.printQualifiedName(out);
			else if constexpr (PP::concepts::derived_from<Node, clang::Type>)
			{
				clang::QualType::print(&node,
				                       clang::Qualifiers(),
				                       out,
				                       printing_policy,
				                       "");
			}
		}
		void print_name(llvm::raw_ostream& out) const override final
		{
			if constexpr (PP::concepts::derived_from<Node, clang::NamedDecl>)
				node.printName(out);
			else if constexpr (PP::concepts::derived_from<Node, clang::Type>)
			{
				auto pp = printing_policy;
				pp.SuppressScope = 1;

				clang::QualType::print(&node, clang::Qualifiers(), out, pp, "");
			}
		}

	protected:
		///
		/// @brief Gets the associated AST node.
		///
		/// @return A reference to the associated AST node.
		///
		const Node& get_node() const
		{
			return node;
		}
	};
}
