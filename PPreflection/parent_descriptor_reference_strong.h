#pragma once
#include "PP/variant.hpp"

#include "descriptor.h"

namespace PPreflection
{
	class Namespace;

	namespace detail
	{
		using parent_descriptor_reference_strong_base =
			PP::variant<const class_type&, const Namespace&>;
	}

	class parent_descriptor_reference_strong
		: public descriptor
		, public detail::parent_descriptor_reference_strong_base
	{
	public:
		constexpr parent_descriptor_reference_strong(
			const class_type&) noexcept;
		constexpr parent_descriptor_reference_strong(const Namespace&) noexcept;

		constexpr const Namespace* as_namespace() const noexcept;
		constexpr const class_type* as_class() const noexcept;

		constexpr void print_name_before_parent(
			PP::simple_ostream& out) const noexcept override final;
		constexpr void print_name_after_parent(
			PP::simple_ostream& out) const noexcept override final;
		constexpr parent_descriptor_reference get_parent(
			void*) const noexcept override final;
		constexpr bool has_name(
			PP::string_view name) const noexcept override final;

		constexpr operator parent_descriptor_reference() const noexcept;
	};
}
