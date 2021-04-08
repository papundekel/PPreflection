#pragma once
#include "PP/static_cast.hpp"
#include "PP/variant.hpp"

#include "make_equal_operator_visitor.h"
#include "non_array_object_type.h"
#include "reference_type.h"
#include "void_type.h"

namespace PPreflection
{
	namespace detail
	{
		using return_type_reference_base = PP::variant<const reference_type&, const non_array_object_type&, const void_type&>;
	}

	class return_type_reference : public detail::return_type_reference_base
	{
	public:
		constexpr return_type_reference(const reference_type& t)
			: detail::return_type_reference_base(PP::placeholder, t)
		{}
		constexpr return_type_reference(const non_array_object_type& t)
			: detail::return_type_reference_base(PP::placeholder, t)
		{}
		constexpr return_type_reference(const void_type& t)
			: detail::return_type_reference_base(PP::placeholder, t)
		{}

		constexpr const type& as_type() const noexcept
		{
			return PP::visit(PP::static__cast * PP::type<const type&>, *this);
		}

		constexpr operator const type&() const noexcept
		{
			return as_type();
		}

		constexpr bool operator==(return_type_reference other) const noexcept
		{
			return PP::visit(make_equal_operator_visitor(other), *this);
		}
	};
}
