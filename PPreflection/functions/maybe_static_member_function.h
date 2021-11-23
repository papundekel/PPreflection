#pragma once
#include "function.h"

namespace PPreflection
{
class class_type;

///
/// @brief Represents a non-namespace function.
///
class maybe_static_member_function : public function
{
public:
	///
	/// @brief Gets the parent class.
	///
	constexpr virtual const class_type& get_parent() const noexcept = 0;

private:
	constexpr class_or_namespace get_parent(int) const noexcept override final
	{
		return get_parent();
	}
};
}
