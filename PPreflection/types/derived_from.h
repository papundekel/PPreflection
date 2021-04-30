#pragma once
#include "non_union_class_type.h"

namespace PPreflection
{
	namespace
	{
		constexpr void fill_with_base_classes(const non_union_class_type& c,
											  auto&						  stack)
		{
			for (const non_union_class_type& base : c.get_base_classes())
				stack.push_back(base);
		}
	}

	constexpr bool derived_from(const non_union_class_type& derived,
								const non_union_class_type& base)
	{
		PP::small_optimized_vector<
			PP::reference_wrapper<const non_union_class_type&>,
			8>
			stack;

		fill_with_base_classes(derived, stack);

		while (!stack.empty())
		{
			const non_union_class_type& b = stack.pop_back();
			if (b == base)
				return true;
			else
				fill_with_base_classes(b, stack);
		}

		return false;
	}

	constexpr auto derived_from(const type& derived, const type& base)
	{
		const auto* non_union_class_derived_ptr =
			dynamic_cast<const non_union_class_type*>(&derived);
		const auto* non_union_class_base_ptr =
			dynamic_cast<const non_union_class_type*>(&base);
		bool result = false;

		if (non_union_class_derived_ptr && non_union_class_base_ptr)
		{
			result = derived_from(*non_union_class_derived_ptr,
								  *non_union_class_base_ptr);
		}

		return PP::make_tuple(
			result, non_union_class_derived_ptr, non_union_class_base_ptr);
	}

	constexpr bool same_or_derived_from(const type& derived, const type& base)
	{
		if (derived == base)
			return true;

		return derived_from(derived, base)[PP::value_0];
	}
}
