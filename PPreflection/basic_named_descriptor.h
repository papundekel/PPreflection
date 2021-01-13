#pragma once
#include "descriptor.h"
#include "reflect.h"

namespace detail
{
	template <typename ID, typename Base>
	class basic_named_descriptor : public Base
	{
	protected:
		constexpr std::string_view get_name() const noexcept
		{
			return this->reflect_name(PP::type_v<std::remove_cv_t<ID>>);
		}

	private:
		constexpr bool has_name(std::string_view name) const noexcept override final
		{
			return get_name() == name;
		}
	};
}
