#pragma once
#include "type_disjunction_reference.hpp"

namespace PPreflection
{
	class descriptor;
	class class_type;
	class Namespace;

	namespace detail
	{
		using parent_descriptor_reference_base = type_disjunction_reference<class_type, Namespace>;
	}

	class parent_descriptor_reference : public detail::parent_descriptor_reference_base
	{
	public:
		using detail::parent_descriptor_reference_base::parent_descriptor_reference_base;

		constexpr operator const descriptor&() const noexcept;
		constexpr const Namespace* as_namespace() const noexcept;
		constexpr const class_type* as_class() const noexcept;
	};
}
