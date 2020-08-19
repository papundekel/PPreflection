#pragma once
#include "function.h"

class namespace_t;
class overloaded_namespace_function;

class namespace_function : public function
{
public:
	constexpr virtual const overloaded_namespace_function& get_overloaded_function() const noexcept = 0;

	constexpr const namespace_t& get_enclosing_namespace() const noexcept;
};
