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
		void print_qualified_name(llvm::raw_ostream& out) const override final;
		void print_name(llvm::raw_ostream& out) const override final;

		void print_unscoped_name(llvm::raw_ostream& out) const override final;
		void print_scoped_name_parent(
			llvm::raw_ostream& out) const override final;
		void print_scoped_name_as_parent(
			llvm::raw_ostream& out) const override final;

		void print_metadata_object(llvm::raw_ostream&) const override final;

		const descriptor* get_parent(void*) const override final;
	};
}
