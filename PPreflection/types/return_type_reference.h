#pragma once
#include "../type_disjunction_reference.hpp"
#include "reference_type.h"
#include "non_array_object_type.h"
#include "void_type.h"
#include "functional/id.hpp"

namespace detail
{
	using return_type_reference_base = type_disjunction_reference<reference_type, non_array_object_type, void_type>;
}

class return_type_reference : public detail::return_type_reference_base
{
public:
	constexpr return_type_reference(const reference_type& rt)
		: detail::return_type_reference_base(rt)
	{}
	constexpr return_type_reference(const non_array_object_type& naot)
		: detail::return_type_reference_base(naot)
	{}
	constexpr return_type_reference(const void_type& vt)
		: detail::return_type_reference_base(vt)
	{}

	constexpr operator const type&() const noexcept
	{
		return visit(PP::id<const type&>);
	}
};
