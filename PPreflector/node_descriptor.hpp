#pragma once
#include "PP/concepts/derived_from.hpp"

#include "pragma_push.hpp"
#include "clang/AST/Decl.h"
#include "clang/AST/PrettyPrinter.h"
#include "pragma_pop.hpp"

#include "descriptor.hpp"

namespace PPreflector
{
	template <typename Node, typename Descriptor = descriptor>
	requires PP::concepts::derived_from<Descriptor, descriptor>
	class node_descriptor : public Descriptor
	{
		const Node& node;

	public:
		node_descriptor(const Node& node, auto&&... args)
			: Descriptor(PP_FORWARD(args)...)
			, node(node)
		{}

		void print_qualified_name(llvm::raw_ostream& out) const
		{
			if constexpr (PP::concepts::derived_from<Node, clang::NamedDecl>)
				node.printQualifiedName(out);
		}
		void print_name(llvm::raw_ostream& out) const
		{
			if constexpr (PP::concepts::derived_from<Node, clang::NamedDecl>)
				node.printName(out);
			else if constexpr (PP::concepts::derived_from<Node, clang::Type>)
				clang::QualType::print(&node, clang::Qualifiers(), out, clang::PrintingPolicy({}), "");
		}

	protected:
		const Node& get_node() const
		{
			return node;
		}
	};
}
