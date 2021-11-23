#pragma once
#include "static_function.hpp"

namespace PPreflector
{
	///
	/// @brief Represents a static member function.
	///
	///
	class static_member_function : public static_function
	{
	public:
		using static_function::static_function;

		void print_metadata_object(llvm::raw_ostream& out) const override final;
	};
}
