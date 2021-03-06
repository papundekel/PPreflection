#pragma once
#include "../parent_descriptor_reference_strong.h"
#include "named_type.h"
#include "non_array_object_type.h"

namespace PPreflection
{
	class user_defined_type : public detail::named_type<non_array_object_type>
	{
		constexpr virtual parent_descriptor_reference get_parent(void*) const noexcept override final
		{
			return get_parent().visit([](const auto& t){ return parent_descriptor_reference(t); });
		}

	public:
		constexpr virtual parent_descriptor_reference_strong get_parent(int = 0) const noexcept = 0;

		constexpr bool operator==(const user_defined_type& other) const noexcept
		{
			return this == &other;
		}
		constexpr bool operator==(const type& other) const noexcept override final
		{
			return compare(*this, other);
		}
	};
}
