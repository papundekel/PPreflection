#pragma once
#include "class_type.h"

namespace PPreflection
{
	namespace
	{
		constexpr void fill_with_base_classes(const class_type& c, auto& stack)
		{
			for (const class_type& base : c.get_base_classes())
				stack.push_back(base);
		}
	}

	constexpr bool derived_from(const class_type& derived, const class_type& base)
	{
		PP::simple_vector<PP::reference_wrapper<const class_type&>> stack;

		fill_with_base_classes(class_derived, stack);

		while (!stack.empty())
		{
			const class_type& base = stack.pop_back();
			if (base == class_base)
			{
				return true;
			}
			else
				fill_with_base_classes(base, stack);
		}

		return false;
	}

	constexpr auto derived_from(const type& derived, const type& base)
	{
		const auto* class_derived_ptr = dynamic_cast<const class_type*>(&derived);
		const auto* class_base_ptr = dynamic_cast<const class_type*>(&base);
		bool result = false;

		if (class_derived_ptr && class_base_ptr)
		{
			result = derived_from(*class_derived_ptr, *class_base_ptr);
		}

		return PP::make_tuple(result, class_derived_ptr, class_base_ptr);
	}
}
