#pragma once
#include "type_disjunction_reference.hpp"

namespace PPreflection
{
	class descriptor;
	class class_type;
	class Namespace;

	constexpr inline struct parent_descriptor_none_tag_t {} parent_descriptor_none_tag{};

	namespace detail
	{
		using parent_descriptor_reference_base = type_disjunction_reference<class_type, Namespace, parent_descriptor_none_tag_t>;
	}

	class parent_descriptor_reference
		: public detail::parent_descriptor_reference_base
	{
	public:
		constexpr parent_descriptor_reference(const class_type&) noexcept;
		constexpr parent_descriptor_reference(const Namespace&) noexcept;
		constexpr parent_descriptor_reference() noexcept;

		constexpr const descriptor* as_descriptor() const noexcept;
		constexpr const Namespace* as_namespace() const noexcept;
		constexpr const class_type* as_class() const noexcept;
	};
}
