#pragma once
#include "constructor.hpp"

namespace PPreflector
{
	class default_constructor : public constructor
	{
	public:
		default_constructor(const descriptor& parent);

		void print_name_header(llvm::raw_ostream& out) const override final;
	};
}
