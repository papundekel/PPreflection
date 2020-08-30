#pragma once
#include "descriptor.h"
#include "simple_ostream.h"
#include "reflect.h"

template <typename T>
constexpr std::string_view descriptor::reflect_name() noexcept
{
	return reflect<detail::name_wrap<T>, std::string_view>();
}

template <typename Descriptor>
constexpr const Descriptor* descriptor::get_descriptor(std::string_view name, simple_range<const cref_t<Descriptor>> descriptors) noexcept
{
	for (const Descriptor& d : descriptors)
		if (d.has_name(name))
			return &(const Descriptor&)d;
	return nullptr;
}
