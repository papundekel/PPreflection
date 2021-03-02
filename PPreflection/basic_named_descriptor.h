#pragma once
#include "PP/remove_cv.hpp"

#include "descriptor.h"
#include "reflect.h"

namespace PPreflection::detail
{
	template <typename ID, typename Base>
	class basic_named_descriptor : public Base
	{
	protected:
		constexpr PP::string_view get_name() const noexcept override final
		{
			return this->reflect_name(~PP::type<ID>);
		}
	};
}
