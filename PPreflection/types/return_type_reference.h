#pragma once
#include "PP/static_cast.hpp"
#include "PP/type_disjunction_reference.hpp"

#include "make_equal_operator_visitor.h"
#include "non_array_object_type.h"
#include "reference_type.h"
#include "void_type.h"

namespace PPreflection
{
	namespace detail
	{
		using return_type_reference_base = PP::type_disjunction_reference<reference_type, non_array_object_type, void_type>;
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

		constexpr const type& as_type() const noexcept
		{
			return visit(PP::static__cast * PP::type<const type&>);
		}

		constexpr operator const type&() const noexcept
		{
			return as_type();
		}

		constexpr bool operator==(return_type_reference other) const noexcept
		{
			return visit(make_equal_operator_visitor(other));
		}
	};
}
