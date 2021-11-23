#pragma once
#include "PP/variant.hpp"

namespace PPreflection
{
class descriptor;
class class_type;
class Namespace;

///
/// @brief Represents a no-parent value in @ref parent_descriptor.
///
struct parent_descriptor_none_tag_t
{};

namespace detail
{
using parent_descriptor_base = PP::
	variant<const class_type&, const Namespace&, parent_descriptor_none_tag_t>;
}

///
/// @brief Represents a union of possible parent descriptors: class, namespace
/// or no parent.
///
class parent_descriptor : public detail::parent_descriptor_base
{
public:
	///
	/// @brief Creates a class parent.
	///
	constexpr parent_descriptor(const class_type&) noexcept;
	///
	/// @brief Creates a namespace parent.
	///
	constexpr parent_descriptor(const Namespace&) noexcept;
	///
	/// @brief Creates a no-parent object.
	///
	constexpr parent_descriptor() noexcept;

	///
	/// @brief Casts to a pointer to a descriptor.
	///
	/// @retval nullptr iff the object is a no-parent.
	///
	constexpr const descriptor* as_descriptor() const noexcept;

	///
	/// @brief Casts to a pointer to a namespace descriptor.
	///
	/// @retval nullptr iff the object is a no-parent or a class.
	///
	constexpr const Namespace* as_namespace() const noexcept;

	///
	/// @brief Casts to a pointer to a class descriptor.
	///
	/// @retval nullptr iff the object is a no-parent or a namespace.
	///
	constexpr const class_type* as_class() const noexcept;
};
}
