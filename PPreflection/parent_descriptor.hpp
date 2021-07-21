#pragma once
#include "parent_descriptor.h"

#include "PP/overloaded.hpp"
#include "PP/static_cast.hpp"

#include "Namespace.h"
#include "descriptor.h"
#include "types/class_type.h"

constexpr PPreflection::parent_descriptor::parent_descriptor(
	const class_type& d) noexcept
	: detail::parent_descriptor_base(PP::placeholder, d)
{}
constexpr PPreflection::parent_descriptor::parent_descriptor(
	const Namespace& d) noexcept
	: detail::parent_descriptor_base(PP::placeholder, d)
{}
constexpr PPreflection::parent_descriptor::parent_descriptor() noexcept
	: detail::parent_descriptor_base(PP::placeholder,
                                     parent_descriptor_none_tag_t{})
{}

constexpr const PPreflection::descriptor*
PPreflection::parent_descriptor::as_descriptor() const noexcept
{
	return PP::visit(PP::overloaded(
						 [](const descriptor& d)
						 {
							 return &d;
						 },
						 [](parent_descriptor_none_tag_t)
						 {
							 return (const descriptor*)nullptr;
						 }),
	                 *this);
}

constexpr const PPreflection::Namespace*
PPreflection::parent_descriptor::as_namespace() const noexcept
{
	return PP::visit(PP::overloaded(
						 [](const Namespace& n)
						 {
							 return &n;
						 },
						 [](const auto&)
						 {
							 return (const Namespace*)nullptr;
						 }),
	                 *this);
}
constexpr const PPreflection::class_type*
PPreflection::parent_descriptor::as_class() const noexcept
{
	return PP::visit(PP::overloaded(
						 [](const class_type& c)
						 {
							 return &c;
						 },
						 [](const auto&)
						 {
							 return (const class_type*)nullptr;
						 }),
	                 *this);
}
