#pragma once
#include "function.h"

namespace PPreflection
{
	class class_type;

	class maybe_static_member_function : public function
	{
	public:
		constexpr virtual const class_type& get_parent() const noexcept = 0;

	private:
		constexpr parent_descriptor_reference_strong get_parent(int) const noexcept override final
		{
			return get_parent();
		}
	};
}
