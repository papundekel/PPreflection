#pragma once
#include "PP/variant.hpp"

namespace PPreflection
{
class descriptor;
class class_type;
class Namespace;

struct parent_descriptor_none_tag_t
{};

namespace detail
{
using parent_descriptor_base = PP::
	variant<const class_type&, const Namespace&, parent_descriptor_none_tag_t>;
}

class parent_descriptor : public detail::parent_descriptor_base
{
public:
	constexpr parent_descriptor(const class_type&) noexcept;
	constexpr parent_descriptor(const Namespace&) noexcept;
	constexpr parent_descriptor() noexcept;

	constexpr const descriptor* as_descriptor() const noexcept;
	constexpr const Namespace* as_namespace() const noexcept;
	constexpr const class_type* as_class() const noexcept;
};
}
