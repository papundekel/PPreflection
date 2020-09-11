#pragma once
#include "type.h"
#include "../types.h"
#include "../reflect.h"

template <typename T>
constexpr const auto& type::reflect() noexcept
{
	return ::reflect<T, const get_class<T>&>();
}
