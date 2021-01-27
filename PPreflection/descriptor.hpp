#pragma once
#include "descriptor.h"
#include "reflect.h"

template <typename T>
constexpr std::string_view descriptor::reflect_name(PP::type_t<T>) noexcept
{
	return ::reflect(PP::type<reflection::name<T>>);
}
