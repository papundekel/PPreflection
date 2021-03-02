#pragma once
#include "PP/add_cv.hpp"
#include "PP/array.hpp"
#include "PP/cv_qualifier.hpp"
#include "PP/view_equal.hpp"

#include "cv_qualifiable_type.h"
#include "non_user_defined_type.h"
#include "pointable_type.h"

namespace PPreflection
{
	class void_type : public detail::non_user_defined_type<detail::cv_qualifiable_type<pointable_type>>
	{
		static constexpr PP::array<PP::string_view, 4> names
		{
			"void",
			"void const",
			"void volatile",
			"void const volatile"
		};

		constexpr size_t get_cv_qualifier_index() const noexcept
		{
			return (size_t)get_cv_qualifier();
		}

	public:
		constexpr void print_name_prefix(PP::simple_ostream& out) const noexcept override final
		{
			out.write(names[get_cv_qualifier_index()]);
		}
		constexpr void print_name_suffix(PP::simple_ostream&) const noexcept override final
		{}
		constexpr bool has_name(PP::string_view name) const noexcept override final
		{
			return PP::view_equal(names[get_cv_qualifier_index()], name);
		}
	};
}
