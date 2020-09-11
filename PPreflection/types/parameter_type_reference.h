#pragma once
#include "../type_disjunction_reference.hpp"
#include "../../PP/PP/view.hpp"
#include "reference_type.h"
#include "non_array_object_type.h"

namespace detail
{
	using parameter_type_reference_base = type_disjunction_reference<reference_type, non_array_object_type>;
}

class parameter_type_reference : public detail::parameter_type_reference_base
{
public:
	constexpr parameter_type_reference(const reference_type& rt)
		: detail::parameter_type_reference_base(rt)
	{}
	constexpr parameter_type_reference(const non_array_object_type& naot)
		: detail::parameter_type_reference_base(naot)
	{}

	constexpr bool can_be_initialized(const reference_type& initializer) const noexcept
	{
		return visit([&initializer](const auto& x) { return x.get().can_be_initialized(initializer); });
	}

	constexpr operator const type&() const
	{
		return visit(PP::id<const type&>);
	}

	constexpr const type* operator&() const
	{
		const type& t = *this;
		return &t;
	}

	static constexpr bool can_initialize_many(PP::view auto&& parameter_types, PP::view auto&& argument_types) noexcept
	{
		if (PP::count(parameter_types) != PP::count(argument_types))
			return false;

		auto a = PP::begin(argument_types);
		for (auto p = PP::begin(parameter_types); p != PP::end(parameter_types); ++p, ++a)
		{
			const reference_type& arg_type = *a;
			parameter_type_reference par_type = *p;

			if (!par_type.can_be_initialized(arg_type))
				return false;
		}

		return true;
	}
};
