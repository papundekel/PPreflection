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

///
/// @brief Represents a union of possible parent descriptors: class, namespace.
///
class class_or_namespace
	: public descriptor
	, public detail::class_or_namespace_base
{
public:
	///
	/// @brief Creates a class parent.
	///
	constexpr class_or_namespace(const class_type&) noexcept;

	///
	/// @brief Creates a namespace parent.
	///
	constexpr class_or_namespace(const Namespace&) noexcept;

	///
	/// @brief Casts to a pointer to a namespace descriptor.
	///
	/// @retval nullptr iff the object is a class.
	///
	constexpr const Namespace* as_namespace() const noexcept;

	///
	/// @brief Casts to a pointer to a class descriptor.
	///
	/// @retval nullptr iff the object is a namespace.
	///
	constexpr const class_type* as_class() const noexcept;

	///
	/// @brief Casts to a @ref parent_descriptor referencing the same entity.
	///
	constexpr operator parent_descriptor() const noexcept;

	constexpr parent_descriptor get_parent(void*) const noexcept override final;

	constexpr bool has_name(PP::string_view name) const noexcept override final;

private:
	constexpr void print_name_before_parent(
		PP::ostream& out) const noexcept override final;
	constexpr void print_name_after_parent(
		PP::ostream& out) const noexcept override final;
};
}
