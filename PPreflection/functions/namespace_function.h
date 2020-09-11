#pragma once
#include "function.h"
#include "../namespace_t.h"

class namespace_function;

class overloaded_namespace_function : public function::overloaded
{
protected:
	constexpr virtual PP::any_view<const namespace_function&> get_namespace_overloads() const noexcept = 0;

public:
	constexpr const namespace_t& get_parent() const noexcept override = 0;

	constexpr PP::view auto get_overloads() const noexcept
	{
		return get_namespace_overloads();
	}
};

class namespace_function : public function
{
public:
	using overloaded = overloaded_namespace_function;

	constexpr const overloaded& get_overloaded_function() const noexcept override = 0;

	constexpr const namespace_t& get_parent() const noexcept override final
	{
		return get_overloaded_function().get_parent();
	}
};
