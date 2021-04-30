#pragma once
#include "pragma_pop.hpp"
#include "pragma_push.hpp"
#include "clang/AST/PrettyPrinter.h"

namespace PPreflector
{
	static auto make_printing_policy() noexcept
	{
		clang::PrintingPolicy policy({});
		policy.SuppressTagKeyword = 1;
		policy.Bool = 1;
		return policy;
	}

	static inline auto printing_policy = make_printing_policy();
}
