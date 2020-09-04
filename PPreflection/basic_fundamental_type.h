#pragma once
#include "basic_type.h"

namespace detail
{
	template <typename T>
	class basic_fundamental_type : public basic_type<T>
	{
	public:
		constexpr const namespace_t* get_namespace() const noexcept override final;
		constexpr const overloaded_constructor* get_constructors() const noexcept override final;
	};
}
