#pragma once
#include "pointer_type.h"
#include "dynamic_cv_qualifiable_type.h"

class dynamic_pointer_type final : public detail::dynamic_cv_qualifiable_type<pointer_type>
{
	const pointable_type& pointed_to_type;

public:
	constexpr explicit dynamic_pointer_type(const pointable_type& pointed_to_type, PP::cv_qualifier cv = PP::cv_qualifier::none) noexcept
		: dynamic_cv_qualifiable_type<pointer_type>(cv)
		, pointed_to_type(pointed_to_type)
	{}

	constexpr virtual const pointable_type& remove_pointer() const noexcept override final
	{
		return pointed_to_type;
	}
};
