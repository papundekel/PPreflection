#pragma once
#include "../type_disjunction_reference.hpp"
#include "non_array_object_type.h"
#include "reference_type.h"
#include "static_cast.hpp"
#include "view.hpp"

namespace PPreflection
{
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
			return visit([&initializer](const auto& x) { return x.can_be_initialized(initializer); });
		}

		constexpr operator const type&() const
		{
			return visit(PP::static__cast * PP::type<const type&>);
		}

		constexpr const type* operator&() const
		{
			const type& t = *this;
			return &t;
		}

		static constexpr bool can_initialize_many(PP::concepts::view auto&& parameter_types, PP::concepts::view auto&& argument_types) noexcept
		{
			if (PP::view_count(parameter_types) != PP::view_count(argument_types))
				return false;

			auto a = PP::view_begin(argument_types);
			for (auto p = PP::view_begin(parameter_types); p != PP::view_end(parameter_types); ++p, ++a)
			{
				const reference_type& arg_type = *a;
				parameter_type_reference par_type = *p;

				if (!par_type.can_be_initialized(arg_type))
					return false;
			}

			return true;
		}
	};
}
