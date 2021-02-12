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
		constexpr std::string_view get_name() const noexcept
		{
			return this->reflect_name(~PP::type<ID>);
		}

	private:
		constexpr bool has_name(std::string_view name) const noexcept override final
		{
			return get_name() == name;
		}
	};
}
