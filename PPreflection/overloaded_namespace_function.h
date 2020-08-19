#pragma once
#include "overloaded_function.h"

class namespace_t;
class namespace_function;

class overloaded_namespace_function : public overloaded_function<namespace_function>
{
public:
	constexpr virtual const namespace_t& get_enclosing_namespace() const noexcept = 0;
};
