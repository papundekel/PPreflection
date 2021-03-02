#pragma once
#include "PP/get_value.hpp"

#include "pointable_type.h"

namespace PPreflection
{
	class dynamic_reference_type;
	class dynamic_lvalue_reference_type;
	class dynamic_rvalue_reference_type;

	class referencable_type : public pointable_type
	{
		constexpr dynamic_lvalue_reference_type make_lreference() const noexcept;
		constexpr dynamic_rvalue_reference_type make_rreference() const noexcept;

	public:
		constexpr auto make_reference(PP::concepts::value auto rvalue) const noexcept;
		constexpr dynamic_reference_type make_reference(bool lvalue) const noexcept;
	};
}
