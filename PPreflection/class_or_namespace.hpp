#pragma once
#include "class_or_namespace.h"

#include "Namespace.h"
#include "parent_descriptor.h"
#include "types/class_type.h"

constexpr PPreflection::class_or_namespace::class_or_namespace(
	const class_type& d) noexcept
	: detail::class_or_namespace_base(PP::placeholder, d)
{}
constexpr PPreflection::class_or_namespace::class_or_namespace(
	const Namespace& d) noexcept
	: detail::class_or_namespace_base(PP::placeholder, d)
{}

constexpr const PPreflection::Namespace*
PPreflection::class_or_namespace::as_namespace() const noexcept
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
PPreflection::class_or_namespace::as_class() const noexcept
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
constexpr void PPreflection::class_or_namespace::print_name_before_parent(
	PP::ostream& out) const noexcept
{
	PP::visit(
		[&out](const descriptor& d)
		{
			d.print_name_before_parent(out);
		},
		*this);
}
constexpr void PPreflection::class_or_namespace::print_name_after_parent(
	PP::ostream& out) const noexcept
{
	PP::visit(
		[&out](const descriptor& d)
		{
			d.print_name_after_parent(out);
		},
		*this);
}
constexpr PPreflection::parent_descriptor
PPreflection::class_or_namespace::get_parent(void*) const noexcept
{
	return PP::visit(
		[](const descriptor& d)
		{
			return d.get_parent();
		},
		*this);
}
constexpr bool PPreflection::class_or_namespace::has_name(
	PP::string_view name) const noexcept
{
	return PP::visit(
		[name](const descriptor& d)
		{
			return d.has_name(name);
		},
		*this);
}

constexpr PPreflection::class_or_namespace::operator parent_descriptor()
	const noexcept
{
	return PP::visit(
		[](const auto& d)
		{
			return parent_descriptor(d);
		},
		*this);
}
