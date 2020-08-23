#pragma once
#include "dynamic_object.h"
#include "simple_range.h"
#include "descriptor.h"

template <typename Function>
class overloaded_function : public descriptor
{
public:
	constexpr virtual simple_range<const cref_t<Function>> get_overloads() const noexcept = 0;

	constexpr dynamic_object invoke(simple_range<const dynamic_reference> args = {}) const;
};
