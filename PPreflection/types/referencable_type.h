#pragma once
#include "pointable_type.h"

class dynamic_reference_type;
class dynamic_lvalue_reference_type;
class dynamic_rvalue_reference_type;

class referencable_type : public pointable_type
{
	constexpr dynamic_lvalue_reference_type make_lreference() const noexcept;
	constexpr dynamic_rvalue_reference_type make_rreference() const noexcept;

public:
	template <bool rvalue>
	constexpr auto make_reference() const noexcept;
	constexpr dynamic_reference_type make_reference(bool lvalue) const noexcept;
};
