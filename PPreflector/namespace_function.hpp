#pragma once
#include "static_function.hpp"

namespace PPreflector
{
	class namespace_function : public static_function
	{
	public:
		using static_function::static_function;

		void print_metadata_object(llvm::raw_ostream& out) const override final;
	};
}
