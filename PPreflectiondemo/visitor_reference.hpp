#pragma once
#include "animals.hpp"

namespace visitors
{
	struct visitor_reference final : animal_visitor
	{
		void visit(animals::ape& ape) override final;
		void visit(animals::bat& bat) override final;
		void visit(animals::cat& cat) override final;
		void visit(animals::dog& dog) override final;
		void visit(animals::elk& elk) override final;
	};
}
