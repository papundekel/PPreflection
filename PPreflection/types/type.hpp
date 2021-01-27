#pragma once
#include "type.h"
#include "types.h"
#include "../reflect.h"
#include <type_traits>

template <typename T>
constexpr const type::get_class<T>& type::reflect_helper(PP::type_t<T>) noexcept
{
	return ::reflect(PP::type<T>);
}
