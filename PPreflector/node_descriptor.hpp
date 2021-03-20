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
		explicit node_descriptor(const Node& node, auto&&... args)
			: Descriptor(PP_FORWARD(args)...)
			, node(node)
		{}

		void print_qualified_name(llvm::raw_ostream& out) const override final
		{
			if constexpr (PP::concepts::derived_from<Node, clang::NamedDecl>)
				node.printQualifiedName(out);
			else if constexpr (PP::concepts::derived_from<Node, clang::Type>)
			{
				auto pp = clang::PrintingPolicy({});
				pp.SuppressTagKeyword = 1;

				clang::QualType::print(&node, clang::Qualifiers(), out, pp, "");
			}
		}
		void print_name(llvm::raw_ostream& out) const override final
		{
			if constexpr (PP::concepts::derived_from<Node, clang::NamedDecl>)
				node.printName(out);
			else if constexpr (PP::concepts::derived_from<Node, clang::Type>)
			{
				auto pp = clang::PrintingPolicy({});
				pp.SuppressScope = 1;
				pp.SuppressTagKeyword = 1;

				clang::QualType::print(&node, clang::Qualifiers(), out, pp, "");
			}
		}

	protected:
		const Node& get_node() const
		{
			return node;
		}
	};
}
