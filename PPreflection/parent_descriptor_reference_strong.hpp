#pragma once
#include "parent_descriptor_reference_strong.h"

constexpr PPreflection::parent_descriptor_reference_strong::parent_descriptor_reference_strong(const class_type& d) noexcept
	: detail::parent_descriptor_reference_strong_base(d)
{}
constexpr PPreflection::parent_descriptor_reference_strong::parent_descriptor_reference_strong(const Namespace& d) noexcept
	: detail::parent_descriptor_reference_strong_base(d)
{}

constexpr const PPreflection::Namespace* PPreflection::parent_descriptor_reference_strong::as_namespace() const noexcept
{
	return visit(PP::overloaded
	(
		[](const Namespace& n) { return &n;	},
		[](const auto&) { return (const Namespace*)nullptr; }
	));
}
constexpr const PPreflection::class_type* PPreflection::parent_descriptor_reference_strong::as_class() const noexcept
{
	return visit(PP::overloaded
	(
		[](const class_type& c) { return &c; },
		[](const auto&) { return (const class_type*)nullptr; }
	));
}
constexpr void PPreflection::parent_descriptor_reference_strong::print_name_before_parent(PP::simple_ostream& out) const noexcept
{
	visit([&out](const descriptor& d) { d.print_name_before_parent(out); });
}
constexpr void PPreflection::parent_descriptor_reference_strong::print_name_after_parent(PP::simple_ostream& out) const noexcept
{
	visit([&out](const descriptor& d) { d.print_name_after_parent(out); });
}
constexpr PPreflection::parent_descriptor_reference PPreflection::parent_descriptor_reference_strong::get_parent(void*) const noexcept
{
	return visit([](const descriptor& d) { return d.get_parent(); });
}
constexpr bool PPreflection::parent_descriptor_reference_strong::has_name(PP::string_view name) const noexcept
{
	return visit([name](const descriptor& d) { return d.has_name(name); });
}

constexpr PPreflection::parent_descriptor_reference_strong::operator parent_descriptor_reference() const noexcept
{
	return visit([](const auto& d) { return parent_descriptor_reference(d); });
}
