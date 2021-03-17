#pragma once

#include "pragma_push.hpp"
#include "llvm/Support/raw_ostream.h"
#include "pragma_pop.hpp"

namespace PPreflector
{
	template <typename F, typename T>
	class print_wrap
	{
		F printing_function;
		const T& printer;

	public:
		print_wrap(F f, const T& printer)
			: printing_function(f)
			, printer(printer)
		{}

		friend llvm::raw_ostream& operator<<(llvm::raw_ostream& out, const print_wrap& pw)
		{
			pw.printing_function(out, pw.printer);
			return out;
		}
	};

	#define PPREFLECTOR_PW(function_name, object) (::PPreflector::print_wrap([](llvm::raw_ostream& out, auto& printer){ printer.function_name(out); }, object))
}
