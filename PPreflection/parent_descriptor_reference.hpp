#pragma once
#include "parent_descriptor_reference.h"

#include "PP/overloaded.hpp"
#include "PP/static_cast.hpp"

#include "Namespace.h"
#include "types/class_type.h"

constexpr PPreflection::parent_descriptor_reference::operator const descriptor&() const noexcept
{
	return visit(PP::static__cast * PP::type<const descriptor&>);
}

constexpr const PPreflection::Namespace* PPreflection::parent_descriptor_reference::as_namespace() const noexcept
{
	return visit(PP::overloaded
	(
		[](const Namespace& n) { return &n;	},
		[](const descriptor&) { return (const Namespace*)nullptr; }
	));
}
constexpr const PPreflection::class_type* PPreflection::parent_descriptor_reference::as_class() const noexcept
{
	return visit(PP::overloaded
	(
		[](const class_type& c) { return &c; },
		[](const descriptor&) { return (const class_type*)nullptr; }
	));
}