#pragma once
#include "member_function.hpp"

namespace PPreflector
{	
	class conversion_function : public member_function<clang::CXXConversionDecl>
	{
	public:
		using member_function<clang::CXXConversionDecl>::member_function;

		void print_metadata_object(llvm::raw_ostream& out) const override final;
		void print_metadata_members(llvm::raw_ostream& out) const override final;
	};
}
