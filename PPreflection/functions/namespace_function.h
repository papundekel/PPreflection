#pragma once
#include "../named_descriptor.h"
#include "../Namespace.h"
#include "function.h"

namespace PPreflection
{
	class namespace_function : public detail::named_descriptor<function>
	{
	public:
		constexpr virtual const Namespace& get_parent() const noexcept = 0;

	private:
		constexpr parent_descriptor_reference_strong get_parent(int) const noexcept override final
		{
			return get_parent();
		}
	};
}
