#pragma once
#include "descriptor.h"
#include "simple_ostream.h"
#include "reflect.h"

template <typename T>
constexpr std::string_view descriptor::reflect_name() noexcept
{
	return reflect<detail::name_wrap<T>, std::string_view>();
}
