#pragma once
#include "function.h"
#include "overloaded_namespace_function.h"

class namespace_t;

class namespace_function : public function
{
public:
	constexpr const overloaded_namespace_function& get_overloaded_function() const noexcept override = 0;

	constexpr const namespace_t& get_enclosing_namespace() const noexcept;
};
