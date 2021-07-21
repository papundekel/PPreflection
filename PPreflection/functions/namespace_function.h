#pragma once
#include "../Namespace.h"
#include "../named_descriptor.h"
#include "function.h"

namespace PPreflection
{
///
/// @brief Represents a namespace function.
///
class namespace_function : public named_descriptor<function>
{
public:
	///
	/// @brief Gets the parent namespace.
	///
	constexpr virtual const Namespace& get_parent() const noexcept = 0;

private:
	constexpr class_or_namespace get_parent(int) const noexcept override final
	{
		return get_parent();
	}
};
}
