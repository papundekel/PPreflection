#pragma once
#include "parent_descriptor_reference.h"

#include "PP/overloaded.hpp"
#include "PP/static_cast.hpp"

#include "descriptor.h"
#include "Namespace.h"
#include "types/class_type.h"

constexpr PPreflection::parent_descriptor_reference::parent_descriptor_reference(const class_type& d) noexcept
	: detail::parent_descriptor_reference_base(d)
{}
constexpr PPreflection::parent_descriptor_reference::parent_descriptor_reference(const Namespace& d) noexcept
	: detail::parent_descriptor_reference_base(d)
{}
constexpr PPreflection::parent_descriptor_reference::parent_descriptor_reference() noexcept
	: detail::parent_descriptor_reference_base(parent_descriptor_none_tag)
{}

constexpr const PPreflection::descriptor* PPreflection::parent_descriptor_reference::as_descriptor()  const noexcept
{
	return visit(PP::overloaded
	(
		[](const descriptor& d) { return &d; },
		[](const parent_descriptor_none_tag_t&) { return (const descriptor*)nullptr; }
	));
}

constexpr const PPreflection::Namespace* PPreflection::parent_descriptor_reference::as_namespace() const noexcept
{
	return visit(PP::overloaded
	(
		[](const Namespace& n) { return &n;	},
		[](const auto&) { return (const Namespace*)nullptr; }
	));
}
constexpr const PPreflection::class_type* PPreflection::parent_descriptor_reference::as_class() const noexcept
{
	return visit(PP::overloaded
	(
		[](const class_type& c) { return &c; },
		[](const auto&) { return (const class_type*)nullptr; }
	));
}
