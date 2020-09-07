#pragma once
#include "overloaded_function.h"

class namespace_t;
class namespace_function;

class overloaded_namespace_function : public overloaded_function
{
protected:
	constexpr virtual any_view<const namespace_function&> get_namespace_overloads() const noexcept = 0;

public:
	constexpr virtual const namespace_t& get_enclosing_namespace() const noexcept = 0;

	constexpr PP::view auto get_overloads() const noexcept
	{
		return get_namespace_overloads();
	}
};
