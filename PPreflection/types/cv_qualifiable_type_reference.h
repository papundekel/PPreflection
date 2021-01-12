#pragma once
#include "object_type.h"
#include "void_type.h"
#include "../type_disjunction_reference.h"

namespace detail
{
	using cv_qualifiable_type_reference_base = type_disjunction_reference<object_type, void_type>;
}

class cv_qualifiable_type_reference : public detail::cv_qualifiable_type_reference_base
{
public:
	using detail::cv_qualifiable_type_reference_base::cv_qualifiable_type_reference_base;

	constexpr PP::cv_qualifier get_cv_qualifier() const noexcept
	{
		return visit([](const auto& x)
			{
				return x.get_cv_qualifier();
			});
	}

	constexpr bool at_least_as_cv_qualified_as(cv_qualifiable_type_reference other) const noexcept
	{
		return get_cv_qualifier() >= other.get_cv_qualifier();
	}
};
