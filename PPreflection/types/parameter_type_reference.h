#pragma once
#include "PP/static_cast.hpp"
#include "PP/variant.hpp"

#include "make_equal_operator_visitor.h"
#include "non_array_object_type.h"
#include "reference_type.h"

namespace PPreflection
{
	namespace detail
	{
		using parameter_type_reference_base =
			PP::variant<const reference_type&, const non_array_object_type&>;
	}

	class parameter_type_reference
		: public detail::parameter_type_reference_base
	{
	public:
		constexpr parameter_type_reference(const reference_type& t)
			: detail::parameter_type_reference_base(PP::placeholder, t)
		{}
		constexpr parameter_type_reference(const non_array_object_type& t)
			: detail::parameter_type_reference_base(PP::placeholder, t)
		{}

		constexpr const type& to_type() const
		{
			return PP::visit(PP::static__cast * PP::type<const type&>, *this);
		}

		constexpr operator const type&() const
		{
			return to_type();
		}

		constexpr const type* operator&() const
		{
			return &(const type&)*this;
		}

		constexpr bool operator==(parameter_type_reference other) const noexcept
		{
			return PP::visit(make_equal_operator_visitor(other), *this);
		}
	};
}
