#pragma once
#include "descriptor.h"
#include "reflect.h"
#include "remove_cv.hpp"

namespace PPreflection::detail
{
	template <typename ID, typename Base>
	class basic_named_descriptor : public Base
	{
	protected:
		constexpr PP::string_view get_name() const noexcept
		{
			return this->reflect_name(~PP::type<ID>);
		}

	private:
		constexpr bool has_name(PP::string_view name) const noexcept override final
		{
			return view_equal(get_name(), name);
		}
	};
}
