#pragma once
#include "PP/size_t.hpp"

#include "pragma_push.hpp"
#include "llvm/Support/raw_ostream.h"
#include "pragma_pop.hpp"

namespace PPreflector
{	
	class descriptor
	{
	public:
		virtual ~descriptor();

		virtual void print_metadata_name_header(llvm::raw_ostream& out) const = 0;
		virtual void print_metadata_name_own(llvm::raw_ostream& out) const = 0;
		virtual void print_metadata_name_foreign(llvm::raw_ostream& out) const = 0;
		virtual void print_metadata_implementation(llvm::raw_ostream& out) const = 0;

		void print_metadata(llvm::raw_ostream& out) const;
	};
}
