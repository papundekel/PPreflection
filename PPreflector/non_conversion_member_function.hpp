#pragma once
#include "member_function.hpp"

namespace PPreflector
{	
	class non_conversion_member_function : public member_function<clang::CXXMethodDecl>
	{
	public:
		using member_function<clang::CXXMethodDecl>::member_function;

		void print_metadata_object(llvm::raw_ostream& out) const override final;
		void print_metadata_members(llvm::raw_ostream& out) const override final;
	};
}
