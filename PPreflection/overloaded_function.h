#pragma once
#include "dynamic_object.h"
#include "pointer_view.hpp"
#include "descriptor.h"

template <typename Function>
class overloaded_function : public descriptor
{
public:
	using overload_type = Function;

	constexpr virtual pointer_view<const cref_t<Function>> get_overloads() const noexcept = 0;

	constexpr dynamic_object invoke(pointer_view<const dynamic_reference> args = {}) const;
};
