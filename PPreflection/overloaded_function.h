#pragma once
#include "dynamic_wrap.h"
#include "simple_range.h"
#include "descriptor.h"

template <typename Function>
class overloaded_function : public descriptor
{
public:
	constexpr virtual simple_range<const cref_t<Function>> get_overloads() const noexcept = 0;

	constexpr dynamic_wrap invoke(simple_range<const dynamic_ptr> args = {}) const;
};
