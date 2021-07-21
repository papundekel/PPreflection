#pragma once
#include "PP/variant.hpp"

#include "descriptor.h"

namespace PPreflection
{
class Namespace;

namespace detail
{
using class_or_namespace_base =
	PP::variant<const class_type&, const Namespace&>;
}

class class_or_namespace
	: public descriptor
	, public detail::class_or_namespace_base
{
public:
	constexpr class_or_namespace(const class_type&) noexcept;
	constexpr class_or_namespace(const Namespace&) noexcept;

	constexpr const Namespace* as_namespace() const noexcept;
	constexpr const class_type* as_class() const noexcept;

	constexpr void print_name_before_parent(
		PP::ostream& out) const noexcept override final;
	constexpr void print_name_after_parent(
		PP::ostream& out) const noexcept override final;
	constexpr parent_descriptor get_parent(void*) const noexcept override final;
	constexpr bool has_name(PP::string_view name) const noexcept override final;

	constexpr operator parent_descriptor() const noexcept;
};
}
