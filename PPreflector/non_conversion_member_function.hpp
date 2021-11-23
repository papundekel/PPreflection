#pragma once
#include "member_function.hpp"

namespace PPreflector
{
	///
	/// @brief Represents a non-conversion member function.
	///
	///
	class non_conversion_member_function
		: public member_function<clang::CXXMethodDecl>
	{
	public:
		using member_function<clang::CXXMethodDecl>::member_function;

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
