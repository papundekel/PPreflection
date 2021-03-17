#pragma once
#include "Namespace.hpp"

namespace PPreflector
{
	class global_namespace : public Namespace
	{
	public:
		global_namespace();

	private:
		void print_name_parent(llvm::raw_ostream& out) const override final;
		void print_name_simple(llvm::raw_ostream& out) const override final;
		void print_name_simple_no_prefix(llvm::raw_ostream&) const override final;
		void print_name(llvm::raw_ostream& out) const override final;
		void print_preamble(llvm::raw_ostream&) const override final;
	};
}
