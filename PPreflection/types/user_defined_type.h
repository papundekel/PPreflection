#pragma once
#include "../parent_descriptor_reference.h"
#include "non_array_object_type.h"

namespace PPreflection
{
	class user_defined_type : public non_array_object_type
	{
	public:
		constexpr virtual parent_descriptor_reference get_parent(int = 0) const noexcept = 0;

	private:
		constexpr const descriptor& get_parent() const noexcept override final
		{
			return get_parent(0);
		}
	};
}
